//
//
// convert_ansi - unixtools
// Version 1.0
//
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include "CFileIO2.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc ==  3)
	{
		CFileIO2 finp;
		CFileIO2 fout;
		long FileSize;


		const unsigned char* FileData = (const unsigned char*) finp.ReadFile(argv[1], &FileSize);
		

		if (FileData != NULL)
		{
			if (fout.OpenFileWrite(argv[2], ios::binary))
			{
				for (int i = 0; i < FileSize; i++)
				{
				  if (FileData[i] < 128)
				  {
				    fout.WriteBytes(FileData + i, 1);
				  }
				  else
				  {				
				    std::stringstream esc;
				    esc << "\\" << std::oct << (int) FileData[i];				    
				    fout.WriteString(esc.str().c_str());
				  }
				}
				fout.CloseFile();   				
			}
		}
		else
		{
			cout << "***** cannot open file:" << argv[1] << endl;
		}
	}
	else
	{
		cout << "usage: convert_ansi <infile.txt> <outfile.txt>" << endl;
    cout << "Version 1.0" << endl;
	}

	return 0;
}

