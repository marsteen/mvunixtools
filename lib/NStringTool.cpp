//------------------------------------------------------------------------------
//
// PROJECT : 3D Globus
//
// FILE    : NStringTool.cpp
//
// VERSION : 1.0
//
// AUTOR   : Martin Steen
//           Imagon GmbH
//
//
//
//------------------------------------------------------------------------------
//
// Inhalt: Implementation von NStringTool
//
//------------------------------------------------------------------------------
// Revisionsgeschichte:
//
// 02.11.2007 erstellt - Martin Steen
// 20.07.2010 erweitert - Martin Steen
//
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>


#include <NStringTool.h>

namespace NStringTool
{
	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    Split
	//
	//---------------------------------------------------------------------------

	int Split(std::string InputString, stringvector* ResultVector, char SplitChar)
	{
		int OldIndex = 0;
		int NewIndex;

		do
		{
			NewIndex = InputString.find(SplitChar, OldIndex);

			if (NewIndex != std::string::npos)
			{
				ResultVector->push_back(InputString.substr(OldIndex, NewIndex - OldIndex));
				OldIndex = NewIndex + 1;
			}
			else
			{
				ResultVector->push_back(InputString.substr(OldIndex, InputString.size() - OldIndex));
			}
		}
		while (NewIndex != std::string::npos);

		return ResultVector->size();
	}

  //---------------------------------------------------------------------------
  //
  // Namespace:  NStringTool
  // Methode:    Split
  //
  // Splittet einen String in zwei Teile durch das Zeichen SplitChar
  //
  // Return     true = Zeichen gefunden
  //            false = Zeichen NICHT gefunden (kein Ergebnis)
  //
  //---------------------------------------------------------------------------

  bool Split(std::string InputString, std::string& s1, std::string& s2, char SplitChar)
  {
    bool r;
    int OldIndex = 0;
    int NewIndex;

    NewIndex = InputString.find(SplitChar, OldIndex);

    if (NewIndex != std::string::npos)
    {
      s1 = InputString.substr(OldIndex, NewIndex - OldIndex);
      OldIndex = NewIndex + 1;

      s2 = InputString.substr(OldIndex, InputString.size() - OldIndex);

      r = true;
    }
    else
    {
      r = false;
    }

    return r;
  }


	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    Split
	//
	//---------------------------------------------------------------------------

	int Split(std::string InputString, stringvector* ResultVector, char SplitChar, const char b0, const char b1)
	{
		int BrackedOpen = 0;
		std::string InputStringTrimmed;

		for (int i = 0; i < InputString.size(); i++)
		{
			char c = InputString.at(i);
			if (c == b0)
			{
				BrackedOpen += 1;
			}
			else
			if (c == b1)
			{
				BrackedOpen -= 1;
			}
			else
			{
				if ((BrackedOpen > 0) && (c == SplitChar))
				{
					InputStringTrimmed += '*';
				}
				else
				{
					InputStringTrimmed += c;
				}
			}
		}

		//std::cout << "InputStringTrimmed=" << InputStringTrimmed << std::endl;
		int r = Split(InputStringTrimmed, ResultVector, SplitChar);

		for (stringvector::iterator it = ResultVector->begin(); it != ResultVector->end(); ++it)
		{
			for (int i = 0; i < it->size(); i++)
			{
				if ((*it)[i] == '*')
				{
					(*it)[i] = SplitChar;
				}
			}

		}
		return r;
	}



	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    Trim
	//
	//---------------------------------------------------------------------------

	std::string Trim(std::string InStr, const char* trimChars)
	{
		std::string OutStr;
		std::string::size_type StartIndex;
		std::string::size_type EndIndex;

		StartIndex = InStr.find_first_not_of(trimChars);



		if (StartIndex != std::string::npos)
		{
			EndIndex = InStr.find_last_not_of(trimChars);
			if (EndIndex != std::string::npos)
			{
				if (EndIndex >= StartIndex)
				{
					OutStr = InStr.substr(StartIndex, EndIndex - StartIndex + 1);
				}
			}
		}

		return OutStr;
	}



	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    TrimValid
	//
	//---------------------------------------------------------------------------

	std::string TrimValid(std::string InStr, const char* validChars)
	{
		std::string OutStr;
		std::string::size_type StartIndex;
		std::string::size_type EndIndex;

		StartIndex = InStr.find_first_of(validChars);



		if (StartIndex != std::string::npos)
		{
			EndIndex = InStr.find_last_of(validChars);
			if (EndIndex != std::string::npos)
			{
				if (EndIndex >= StartIndex)
				{
					OutStr = InStr.substr(StartIndex, EndIndex - StartIndex + 1);
				}
			}
		}

		return OutStr;
	}

//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Trim
//
//---------------------------------------------------------------------------

void Trim(stringvector& sv, const char* trimChars)
{
	for (int i = 0; i < sv.size(); i++)
	{
		sv[i] = Trim(sv[i], trimChars);
	}

}

//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    TrimValid
//
//---------------------------------------------------------------------------

void TrimValid(stringvector& sv, const char* validChars)
{
	for (int i = 0; i < sv.size(); i++)
	{
		sv[i] = TrimValid(sv[i], validChars);
	}

}



	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    ReadLine
	//
	//---------------------------------------------------------------------------

	int ReadLine(std::ifstream& ifile, std::string* Line)
	{
		char ch;
		bool EndLine = false;

		Line->clear();
		do
		{
			ifile.get(ch);
			if (!ifile.eof())
			{
				if (ch != 0x0D)
				{
					if (ch != 0x0A)
					{
						Line->push_back(ch);
					}
					else
					{
						EndLine = true;
					}
				}
			}
			else
			{
				EndLine = true;
			}
		}
		while (!EndLine);
		return true;
	}

#if 0
	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:
	//
	//---------------------------------------------------------------------------

	std::string FilterUmlaut(const std::string& InStr)
	{
		std::string OutStr;

		for (int i = 0; i < InStr.size(); i++)
		{
			char c = InStr[i];

			switch (c)
			{
				case 'Ä': OutStr += "Ae"; break;
				case 'Ö': OutStr += "Oe"; break;
				case 'Ü': OutStr += "Ue"; break;
				case 'ä': OutStr += "ae"; break;
				case 'ö': OutStr += "Oe"; break;
				case 'ü': OutStr += "Ue"; break;

				default: OutStr += c; break;
			}
		}
		return OutStr;
	}

	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:
	//
	//---------------------------------------------------------------------------


	void RemoveUmlaut(char* c1, bool ToUpper)
	{
		if (ToUpper)
		{
			switch (*c1)
			{
				case 'Ä': *c1 = 'A'; break;
				case 'Ö': *c1 = 'O'; break;
				case 'Ü': *c1 = 'U'; break;
				case 'ä': *c1 = 'A'; break;
				case 'ö': *c1 = 'O'; break;
				case 'ü': *c1 = 'U'; break;

				default: *c1 = toupper(*c1); break;
			}
		}
		else
		{
			switch (*c1)
			{
				case 'Ä': *c1 = 'A'; break;
				case 'Ö': *c1 = 'O'; break;
				case 'Ü': *c1 = 'U'; break;
				case 'ä': *c1 = 'a'; break;
				case 'ö': *c1 = 'o'; break;
				case 'ü': *c1 = 'u'; break;
			}
		}
	}
	#endif


	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:
	//
	// IgnoreCase = true  : Gross/Kleinschreibung ignorieren
	// IgnoreCase = false : Gross/Kleinschreibung beruecksichtigen
	//
	// Rueckgabe: Es wird "true" zurückgegeben, wenn str1 kleiner als str2 ist.
	//            Sonst "false".
	//
	//
	//---------------------------------------------------------------------------


	bool CompareStrings(const std::string& str1, const std::string& str2, bool IgnoreCase)
	{
		bool EndString = false;
		bool r = false;
		int  i = 0;

		const char* cstr1 = str1.c_str();
		const char* cstr2 = str2.c_str();

		do
		{
			char c1 = cstr1[i];
			char c2 = cstr2[i];

			i++;

			if ((c1 == 0) && (c2 == 0))
			{
				EndString = true;
				r = true; // gleich
			}
			else
			{
				if (c1 == 0)
				{
					EndString = true;
				}
				if (c2 == 0)
				{
					EndString = true;
					r = true;
				}
			}

			if (!EndString)
			{
				//RemoveUmlaut(&c1, IgnoreCase);
				//RemoveUmlaut(&c2, IgnoreCase);

				if (c1 < c2)
				{
					r = true;
					EndString = true;
				}
				if (c1 > c2)
				{
					EndString = true;
				}
			}
		}
		while (!EndString);

		return r;
	}


	//---------------------------------------------------------------------------
	//
	// Namespace:  NStringTool
	// Methode:    RemoveExtension
	//
	//
	//
	//---------------------------------------------------------------------------


	std::string RemoveExtension(const std::string& InStr)
	{
		std::string::size_type idx = InStr.find('.');
		if (idx == std::string::npos)
		{
			return InStr;
		}
		return InStr.substr(0, idx);
	}


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    RemoveExtension
//
//
//
//---------------------------------------------------------------------------

std::string Shorten(const std::string& InString, const std::string Punkte, int Limit)
{
	std::string OutString;

	if (InString.size() < Limit)
	{
		OutString = InString;
	}
	else
	{
		OutString = InString.substr(0, Limit) + Punkte;
	}
	return OutString;
}


/*
	//---------------------------------------------------------------------------
	//
	// Namespace: NStringTool
	// Methode:		Strcmpx
	//
	// Vergleich zweier Strings ohne Beruecksichtigung der Gross/Klein-
	// schreibung
	//
	// Return: wie strcmp (0: Strings sind gleich)
	//
	//---------------------------------------------------------------------------

	int Strcmpx(const char* s1, const char* s2)
	{
		if ((s1 == NULL) || (s2 == NULL))
		{
			return false;
		}

		char* bstr1 = new char[strlen(s1) + 1];
		char* bstr2 = new char[strlen(s2) + 1];

		strcpy(bstr1, s1);
		strcpy(bstr2, s2);

		for (char* c1 = bstr1; *c1 != 0; c1++)
		{
			*c1 = toupper(*c1);
		}
		for (char* c1 = bstr2; *c1 != 0; c1++)
		{
			*c1 = toupper(*c1);
		}

		int s = strcmp(bstr1, bstr2);

		delete bstr2;
		delete bstr1;

		return s;
	}
	*/


  //
	// End of namespace NStringTool
	//
}






