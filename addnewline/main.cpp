//---------------------------------------------------------------------------
//
//	addnewline
//
//  Haengt an eine Datei ein Newline-Zeichen an, wenn dieses fehlt
//
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

// Windows: 0x0D 0x0A
// Linux:   0x0A

enum EFileFormat
{
	EFILEFORMAT_VOID,
	EFILEFORMAT_WINDOWS,
	EFILEFORMAT_LINUX
};

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   GetFileFormat
//
//
//
//
//---------------------------------------------------------------------------

static EFileFormat GetFileFormat(const char* Filename)
{

	EFileFormat FileFormat = EFILEFORMAT_VOID;
	char LastChar = 0;
	ifstream infile;

	infile.open(Filename, ios::binary);

	if (infile.good())
	{
		while (!infile.eof())
		{
			char c = infile.get();
			if (c == 0x0A)
			{
				if (LastChar != 0)
				{
					if (LastChar == 0x0D)
					{
						FileFormat = EFILEFORMAT_WINDOWS;
					}
					else
					{
						FileFormat = EFILEFORMAT_LINUX;
					}
					infile.close();
					break;
				}
			}
			LastChar = c;
		}
	}
	return FileFormat;
}

//---------------------------------------------------------------------------
//
// Klasse:    global
// Methode:   main
//
//
//
//
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "usage: addnewline <file1> <file2> .. <filex>" << endl;
		cout << "version 1.0.1" << endl;
	}	
	else
	{
		int ChangedFiles = 0;

		for (int i = 1; i < argc; i++)
		{
			ifstream infile;
			EFileFormat FileFormat = GetFileFormat(argv[i]);

			infile.open(argv[i], ios::binary);
			if (infile.good())
			{
				infile.seekg(-1, ios::end);
				char c = infile.get();
				infile.close();

				switch (FileFormat)
				{
					case EFILEFORMAT_LINUX:

						cout << argv[i] << " - Fileformat is LINUX" << endl;				
						if (c != 0x0A)
						{
							cout << " adding newline 0x0A" << endl;
							ofstream outfile;
							outfile.open(argv[i], ios::binary | ios::app);
							outfile.put(0x0A);
							outfile.close();
							ChangedFiles++;
						}
						break;

					case EFILEFORMAT_WINDOWS:

						cout << argv[i] << " - Fileformat is WINDOWS" << endl;
						if (c != 0x0A)
						{
							cout << " adding newline 0x0D 0x0A" << endl;
							ofstream outfile;
							outfile.open(argv[i], ios::binary | ios::app);
							outfile.put(0x0D);
							outfile.put(0x0A);
							outfile.close();
							ChangedFiles++;
						}
						break;

				}

				//cout << "Letztes Zeichen in der Datei:" << (int) c << endl;
			}
		}
		cout << "Changed files: " << 	ChangedFiles << endl;
	}
	return 0;
}
