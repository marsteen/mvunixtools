//
//
// renamefile - unixtools
// Version 1.0
//
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <NStringTool.h>
#include <CFileIO2.h>
#include <CHexConv.h>

using namespace std;

// renamefile datei --config config.txt
// 0          1     2        3


static void ShowStringHex(const std::string& str)
{
    for (int i = 0; i < str.size(); i++)
    {        
        cout << str[i] << "  ";
    }
    cout << endl;       
    for (int i = 0; i < str.size(); i++)
    {        
        cout << CHexConv::ToHex(str[i]) << " ";
    }
    cout << endl;
}


int main(int argc, char* argv[])
{
    bool replaced = false;
    std::string newFilename;
    
    
    
    
    if (std::string(argv[2]) == "--config")
    {	
        stringvector sv;
        std::string line;
        CFileIO2 fio;
        fio.OpenFileRead(argv[3], ios::binary);
        newFilename = argv[1];
        while (fio.ReadSplitLine(&sv, '*', &line))
        { 
            if (line.size() > 0)
            {
                if (sv.size() >= 2)
                {
                    //cout << "str1=" << "'" << sv[0] << "'" << endl;
                    //cout << "str2=" << "'" << sv[1] << "'" << endl;
                    //ShowStringHex(line);
                    newFilename = NStringTool::ReplaceStrings(newFilename, sv[0], sv[1]);
                }
                else
                {
                    cout << "Fehler in config-Datei, Felder müssen durch * getrennt sein." << endl;
                }
            }
        }
        fio.CloseFile();        
        replaced = true;
    }
    else
	if (argc == 3)
	{
        newFilename = NStringTool::ReplaceStrings(argv[1], argv[2], "");
        replaced = true;                
	}
	else
	if (argc == 4)
	{
        newFilename = NStringTool::ReplaceStrings(argv[1], argv[2], argv[3]);
        replaced = true;        
	}	
	
    if (replaced)
    {
        if (newFilename != argv[1])
        {
            ShowStringHex(argv[1]);
            cout << "old filename:" << argv[1] << endl;
            cout << "new filename:" << newFilename << endl;
            rename(argv[1], newFilename.c_str());
        }
    }
    else
	if (!replaced)
	{
		cout << "usage: renamefile <file> <replace_this_string> <by_this_string>" << endl;
		cout << "   or: renamefile <file> <delete_this_string>" << endl;
        cout << "   or: renamefile <file> --config <configfile.txt>" << endl;
        cout << "Version 2.0" << endl;
	}

	return 0;
}
