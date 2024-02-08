//
//
// replaceinfiles - unixtools
// Version 1.0
//
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <CFileIO2.h>
#include <CHexConv.h>

using namespace std;

//---------------------------------------------------------------------------
//
// ReplaceInFile
//
// Replace srcString with dstString 
// 
//
// filenameIn: name of the input file
// filenameOut: name of the output file
// srcString: string that gets replaced 
// dstString: string that replaces srcString
//
//---------------------------------------------------------------------------

static bool ReplaceInFile(const char* filenameIn, const char* filenameOut, const char* srcString, const char* dstString)
{
    CFileIO2 fin;
    CFileIO2 fout;
    long FileSize;
    bool r = false;

    const char* FileData = (const char*) fin.ReadFile(filenameIn, &FileSize);
    const char* fromptr = FileData;

    if (FileData != NULL)
    {
        int FoundCounter = 0;

        const char* posptr = strstr(FileData, srcString);
        if (posptr != NULL)
        {
            if (fout.OpenFileWrite(filenameOut, ios::binary))
            {
                r = true;
                while (posptr != NULL)
                {
                    fout.WriteBytes(fromptr, posptr - fromptr);
                    if (dstString != NULL)
                    {
                        fout.WriteString(dstString); // Ersatzstring schreiben
                    }
                    fromptr = posptr + strlen(srcString);
                    posptr = strstr(fromptr, srcString);
                    FoundCounter++;
                }

                fout.WriteBytes(fromptr, FileSize - (fromptr - FileData));
            }
            fout.CloseFile();
            cout << "replaced " << FoundCounter << " in " << filenameIn << endl;
        }
    }
    return r;
}


//---------------------------------------------------------------------------
//
// fileExists
//
// return 
// true: file exists
//
//---------------------------------------------------------------------------

static bool fileExists(const std::string filename)
{
    std::filesystem::path f{ filename };
    return std::filesystem::exists(f);
}

//---------------------------------------------------------------------------
//
// replaceAsciiCodesg
//
// return 
// true: ersetzt $xx im String mit Asci-Code
//
//---------------------------------------------------------------------------

static std::string replaceAsciiCodes(const std::string inputStr)
{
    std::string outputStr;
    for (int i = 0; i < inputStr.size(); i++)
    {
        if ((inputStr[i] == '$') &&  (inputStr[i+1] == 'X'))
        {
            int code = CHexConv::ByteToInt(inputStr[i+2], inputStr[i+3]);            
            outputStr += (char) code;
            i += 3;

        }
        else
        {
            outputStr += inputStr[i];
        }
    }
    return outputStr;
}

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	std::string err;
    bool replaced = false;


    if (argc >= 3)
    {
	    if (std::string(argv[2]) == "--rtabs")
	    {
	        ReplaceInFile(argv[1], argv[1], "\t", "    ");
	        replaced = true;
	    }
	    else
	    if (std::string(argv[2]) == "--config")
	    {	
	        ifstream infile(argv[3]);
	        std::string str1;
	        std::string str2;
	        infile >> str1;
	        infile >> str2;
	        infile.close();
	        ReplaceInFile(argv[1], argv[1], str1.c_str(), str2.c_str());
	        replaced = true;
	    }
	    else
	    if (argc == 3)
	    {
            const std::string srcString = replaceAsciiCodes(argv[2]);

	        ReplaceInFile(argv[1], argv[1], srcString.c_str(), NULL);
	        replaced = true;
	    }
	    else
	    if (argc == 4)
	    {
            const std::string srcString = replaceAsciiCodes(argv[2]);
            const std::string dstString = replaceAsciiCodes(argv[3]);

	        ReplaceInFile(argv[1], argv[1], srcString.c_str(), dstString.c_str());
	        replaced = true;
	    }
	}
	

    if (argc >= 2)
    {    	
        if (std::string(argv[2]) == "--rtabs")
        {
            if (!fileExists(argv[1]))
            {
                err = std::string("***** file not found:") + argv[1];
            }
            else
            {
                ReplaceInFile(argv[1], argv[1], "\t", "    ");
                replaced = true;
            }
        }
        else
        if (std::string(argv[2]) == "--config")
        {
            if (!fileExists(argv[1]))
            {
                err = std::string("***** file not found:") + argv[1];
            }
            else
            if (!fileExists(argv[3]))
            {
                err = std::string("***** file not found:") + argv[3];
            }
            else
            {
                ifstream infile(argv[3]);
                std::string str1;
                std::string str2;
                infile >> str1;
                infile >> str2;
                infile.close();
                ReplaceInFile(argv[1], argv[1], str1.c_str(), str2.c_str());
                replaced = true;
            }
        }
        else
        if (argc == 3)
        {
            if (!fileExists(argv[1]))
            {
                err = std::string("***** file not found:") + argv[1];
            }
            else
            {
                ReplaceInFile(argv[1], argv[1], argv[2], NULL);
                replaced = true;
            }
        }
        else
        if (argc == 4)
        {
            if (!fileExists(argv[1]))
            {
                err = std::string("***** file not found:") + argv[1];
            }
            else
            {
                ReplaceInFile(argv[1], argv[1], argv[2], argv[3]);
                replaced = true;
            }
        }
    }

    if (!replaced)
    {
        if (err.size() > 0)
        {
            cout << err << endl;
        }
        cout << "usage: replaceinfile <file> <replace_this_string> <by_this_string>" << endl;
        cout << "   or: replaceinfile <file> <remove_this_string>" << endl;
        cout << "   or: replaceinfile <file> --config config.txt" << endl;
        cout << "   or: replaceinfile <file> --rtabs" << endl;
        cout << "   ascii-hex-codes: \\$X<hexcode> - example: \\$X41 is letter A" << endl;
        cout << "Version 1.7" << endl;
    }

    return 0;
}
