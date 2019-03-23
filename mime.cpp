#include <Windows.h>
#include <string>
#include<fstream>
using namespace std;

string GetMimeType(const string &szExtension)
{
    HKEY hKey = NULL;
    string size = "application/unknown";

    if (RegOpenKeyEx(HKEY_CLASSES_ROOT, szExtension.c_str(), 
                       0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        char szBuffer[256] = {0};
        DWORD dwBuffSize = sizeof(szBuffer);

        if (RegQueryValueEx(hKey, "Content Type", NULL, NULL, 
                       (LPBYTE)szBuffer, &dwBuffSize) == ERROR_SUCCESS)
        {
            size = szBuffer;
        }

        RegCloseKey(hKey);
    }

    return size;
}

int main()
{
	std::ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Welcome\n";
    myfile.close();
    
    string szExt1 = ".pdf";
    string szExt2 = ".txt";

    string szMime1 = GetMimeType(szExt1);
    string szMime2 = GetMimeType(szExt2);

    printf("%s = %s\n%s = %s\n", szExt1.c_str(), szMime1.c_str(), 
        szExt2.c_str(), szMime2.c_str());

    return 0;
}
