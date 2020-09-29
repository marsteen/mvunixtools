//***************************************************************************
//
//
// @PROJECT  :	Diercke Digital PAD Version
// @VERSION  :	1.4
// @FILENAME :	main.cpp
// @DATE     :	23.7.2014
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	msteen@imagon.de
//
//
//***************************************************************************

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <CFileIO2.h>
#include <CDatabaseV6.h>
#include <time.h>


using namespace std;



static CDatabaseV6 db6;

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   Dos2Unix
//
// Loeschen aller CR (0x0D) aus dem Text
//
// Windows: CR LF (0x0D 0x0A)
// Unix: LF (0x0A)
//
//
//---------------------------------------------------------------------------

static void Dos2Unix(char* txt)
{

  int j = 0;
  char* dsttxt = new char[strlen(txt) + 1];
  for (int i = 0; txt[i] != 0; i++)
  {
    if (txt[i] != 0x0D)
    {
      dsttxt[j++] = txt[i];
    } 
  }
  
  dsttxt[j] = 0;
  strcpy(txt, dsttxt);
  delete[] dsttxt;  
}



//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   ExchangeStrings
//
//
//---------------------------------------------------------------------------


// Sucht alle Vorkommen von Keyword in sa uns ersetze sie durch repword
// Das Ergebnis wird in sb gespeichert

static void ExchangeStrings(const std::string& sa, std::string* sb, const std::string& keyword, const std::string& repword)
{
	cout << "Keyword=" << keyword << " repword=" << repword << endl;

	std::string::size_type From = 0;
	std::string::size_type Pos = sa.find(keyword);

	sb->clear();

	while (Pos != std::string::npos)
	{
		cout << "Pos=" << Pos << endl;

		*sb += sa.substr(From, Pos - From);
		*sb += repword;

		From = Pos + keyword.size();
		Pos = sa.substr(From).find(keyword);
	}

	*sb += sa.substr(From);
}

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   ExchangeStrings2
//
//
//---------------------------------------------------------------------------

// Sucht alle Vorkommen von Keyword in sa uns ersetze sie durch repword
// Das Ergebnis wird in sb gespeichert

static void ExchangeStrings2(const std::string& sa, std::string* sb, const std::string& keyword, const std::string& repword)
{
	//cout << "Keyword=" << keyword << " repword=" << repword << endl;
	char LineEnd = 0x0A;

	std::string::size_type From = 0;
	std::string::size_type Pos = sa.find(keyword);

	sb->clear();

	while ((Pos  != std::string::npos) &&
	       (From != std::string::npos))
	{
		//cout << "Pos=" << Pos << " From=" << From << endl;



		*sb += sa.substr(From, Pos - From);

		*sb += keyword;
		*sb += "\t";
		*sb += repword;

		From = Pos + keyword.size();
		while (sa[From] != '\n') From++;

		//From = sa.substr(Pos + keyword.size()).find(LineEnd);
		Pos = sa.substr(From).find(keyword);
	}

	*sb += sa.substr(From);
}


//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   Replace
//
//
//---------------------------------------------------------------------------


static void Replace(const std::string InputString, std::string* OutputString)
{
	std::string String1 = InputString;
	std::string String2;

	std::string *SrcString;
	std::string *DstString;

	bool b = true;

	for (std::vector<stringvector>::iterator it =  db6.mRecords.begin();
	                                         it != db6.mRecords.end();
	                                       ++it)
	{
		if (it->size() == 2)
		{
			if (b)
			{
				SrcString = &String1;
				DstString = &String2;
			}
			else
			{
				SrcString = &String2;
				DstString = &String1;
			}

			ExchangeStrings2(*SrcString, DstString, (*it)[0], (*it)[1]);

			b = !b;
		}
	}

	//cout << "String1=" << String1 << endl;
	//cout << "DstString=" << *DstString << endl;

	*OutputString = *DstString;

}

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   ReadKeymap
//
//
//---------------------------------------------------------------------------

static bool ReadKeymap(const char* Keyfile, const char* Textfile)
{
	bool r =  db6.Read(Keyfile);
	string tstr = Textfile;
	string LocalFile;
	std::string::size_type Slash = tstr.rfind("/");
  stringstream TimeStr;
	
	
  time_t t = time(NULL);
  struct tm tnow = *localtime(&t);
  
  TimeStr << tnow.tm_mday << "." << (tnow.tm_mon + 1) << "." << (tnow.tm_year + 1900);

		
	
	if (Slash != std::string::npos)
	{
	  LocalFile = tstr.substr(Slash + 1);
	}
	else
	{
	  LocalFile = Textfile;
	}
	
	
	if (r)
	{
    for (std::vector<stringvector>::iterator it =  db6.mRecords.begin();
	                                           it != db6.mRecords.end();
	                                         ++it)	   
    {
       if (it->size() == 2)
       {
          std::string* val = &((*it)[1]);
          if (*val == "%FILENAME%")
          {
             *val = LocalFile;
          }
          else
          if (*val == "%DATE%")
          {
             *val = TimeStr.str();
          }           

       }
    }	
	}
	
	return r;
}

// Parameter:
// 1: Keymap
// 2: Eingabedatei

//---------------------------------------------------------------------------
//
// Klasse:    global
// Methode:   main
//
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		if (ReadKeymap(argv[1], argv[2]))
		{
			CFileIO2 fio2;
			int Filesize;
			char* FileData = (char*) fio2.ReadFile(argv[2], &Filesize);

			if (FileData != NULL)
			{
			
			  cout << "Header project / file:" << argv[2] << " keyfile:" << argv[1] << endl;
			
			  Dos2Unix(FileData);
			
			
				string DstFileData;
				string FileDataStr = FileData;
				Replace(FileDataStr, &DstFileData);

				fio2.WriteFile(argv[2], DstFileData.c_str(), DstFileData.size());


				delete[] FileData;
			}
			else
			{
				cout << "***** cannot open source file:" << argv[2] << endl;		
			}
		}
		else
		{
			cout << "***** cannot open key file:" << argv[1] << endl;
		}
	}
	else
	{
		cout << "usage: projectheader <keymapfile> <textfile>" << endl;
    cout << "  Version 1.5" << endl;
	}

	return 0;
}

