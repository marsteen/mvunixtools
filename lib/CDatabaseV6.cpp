#include <fstream>
#include <CDatabaseV6.h>
#include <CFileIO2.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CDatabaseV6
// Methode:   Read
//
//---------------------------------------------------------------------------



bool CDatabaseV6::Get(const std::string Key, std::string* Value)
{
    bool r;
    std::map<std::string, std::string>::iterator it;

    it = mKeyMap.find(Key);
    if (it != mKeyMap.end())
    {
        r = true;
        *Value = it->second;
    }
    else
    {
        r = false;
    }
    return r;
}


#if 0

struct SStringPos
{
    std::string mString;
    const char* mPos;
};


void CDatabaseV6::FillPosSet(const char* text)
{
    set<const char*> PosSet;
    std::vector<stringvector>::iterator it;

    do
    {
        bool PosFound = false;

        for (it = mRecords.begin(); it != mRecords.end(); ++it)
        {
            SStringPos spos;
            spos.mPos = strstr(text, (*it)[0]);
            if (Pos != NULL)
            {
                spos.mString = (*it)[0];
                PosFound = true;
            }
        }
    } while (!PosFound);
}


#endif



//---------------------------------------------------------------------------
//
// Klasse:    CDatabaseV6
// Methode:   Read
//
//---------------------------------------------------------------------------

bool CDatabaseV6::Read(const char* Filename)
{
    bool r = false;
    CFileIO2 fin;

    if (fin.OpenFileRead(Filename, ios::binary))
    {
        r = true;
        stringvector sv;
        while (fin.ReadSplitLine(&sv, '\t'))
        {
            mRecords.push_back(sv);

            if (sv.size() == 2)
            {
                mKeyMap[sv[0]] = sv[1];
            }
        }


        fin.CloseFile();
    }
    return r;
}
