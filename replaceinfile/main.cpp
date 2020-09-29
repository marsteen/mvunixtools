//
//
// replaceinfiles - unixtools
// Version 1.0
//
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include "CFileIO2.h"

using namespace std;

static bool ReplaceInFile(const char* filenameIn, const char* filenameOut, const char* srcString, const char* dstString)
{
	CFileIO2 fin;
	CFileIO2 fout;
	long FileSize;
	bool r = false;

	const char* FileData = (const char*) fin.ReadFile(filenameIn, &FileSize);
	const char* fromptr  = FileData;

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


int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		ReplaceInFile(argv[1], argv[1], argv[2], argv[3]);
	}
	else
	if (argc == 3)
	{
		if (std::string(argv[2]) == "--rtabs")
		{
			ReplaceInFile(argv[1], argv[1], "\t", "    ");
		}
		else
		{	
			ReplaceInFile(argv[1], argv[1], argv[2], NULL);
		}
	}
	else
	{
		cout << "usage: replaceinfile <file> <replace_this_string> <by_this_string>" << endl;
		cout << "   or: replaceinfile <file> <remove_this_string>" << endl;
		cout << "   or: replaceinfile <file> --rtabs" << endl;
    	cout << "Version 1.3" << endl;
	}

	return 0;
}

