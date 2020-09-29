//
//
// renamefile - unixtools
// Version 1.0
//
//

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	if ((argc == 4) || (argc == 3))
	{
		const char* posptr = strstr(argv[1], argv[2]);
	  if (posptr != NULL)
		{
			int  NewLen;
			if (argc == 4)
			{
				NewLen = strlen(argv[1]) + strlen(argv[3]) - strlen(argv[2]);
			}
			else
			{
				NewLen = strlen(argv[1]) - strlen(argv[2]);
			}


			long pos = posptr - argv[1];
			char* NewString = new char[NewLen + 1];

			memset(NewString, 0, NewLen + 1);



			strncpy(NewString, argv[1], pos);
			if (argc == 4)
			{
				strcat(NewString,  argv[3]);
			}
		  strcat(NewString,  posptr + strlen(argv[2]));

			cout << "New name:" << NewString << endl;

			rename(argv[1], NewString);
			delete[] NewString;


		}
	}
	else
	{
		cout << "usage: renamefile <file> <replace_this_string> <by_this_string>" << endl;
		cout << "   or: renamefile <file> <delete_this_string>" << endl;
    cout << "Version 1.2" << endl;
	}

	return 0;
}
