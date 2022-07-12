#include <cstring>
#include "CFileIO2.h"


using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   CFileIO2
//
//---------------------------------------------------------------------------

CFileIO2::CFileIO2()
{
    mOpenWrite = false;
    mOpenRead = false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

bool CFileIO2::OpenFileRead(const char* Filename, OPENMODE OpenMode)
{
    mFs.open(Filename, ios::in | OpenMode);
    mOpenRead = mFs.good();
    return mOpenRead;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

bool CFileIO2::OpenFileWrite(const char* Filename, OPENMODE OpenMode)
{
    mFs.open(Filename, ios::out | OpenMode);
    mOpenWrite = mFs.good();
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   CloseFile
//
//---------------------------------------------------------------------------

void CFileIO2::CloseFile()
{
    mFs.close();
    mOpenWrite = false;
    mOpenRead = false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

long CFileIO2::GetFileSize(const char* Filename)
{
    long FileSize;
    ifstream fin(Filename, ios::in | ios::binary);

    fin.seekg(0, ios::end);
    FileSize = fin.tellg();
    fin.close();
    return FileSize;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   ReadBytes
//
// Parameter: void* buffer - Zeiger auf Puffer, in den die Datei eingelesen
//                           werden
//
//            int nBytes   - Anzahl der Bytes, die eingelesen werden sollen
//
// Return:    true  - Daten wurden eingelesen
//            false - Daten konnten nicht eingelesen werden
//
//
//
// Einlesen einer Anzahl von Bytes aus einer geöffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO2::ReadBytes(void* buffer, int nBytes)
{
    if (mOpenRead)
    {
        mFs.read((char*)buffer, nBytes);
    }
    return mFs.good();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteBytes
//
//
//
// Einlesen einer Anzahl von Bytes aus einer geöffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO2::WriteBytes(const void* buffer, int nBytes)
{
    if (mOpenWrite)
    {
        mFs.write((const char*)buffer, nBytes);
    }
    return mFs.good();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteString
//
//
//---------------------------------------------------------------------------

bool CFileIO2::WriteString(const char* str)
{
    return WriteBytes(str, strlen(str));
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

void* CFileIO2::ReadFile(const char* Filename, long* nBytes)
{
    char* buffer = NULL;

    *nBytes = CFileIO2::GetFileSize(Filename);
    if (*nBytes > 0)
    {
        ifstream fin(Filename, ios::in | ios::binary);
        if (fin.good())
        {
            buffer = new char[*nBytes+1];
            if (buffer != NULL)
            {
                fin.read(buffer, *nBytes);
                buffer[*nBytes] = 0;
            }
        }
        fin.close();
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   ReadLine
//
// Einlesen einer Text-Zeile aus einer Datei
// Die Datei muss im Binaer-Modus geoeffnet sein
//
//---------------------------------------------------------------------------

bool CFileIO2::ReadLine(string* Line)
{
    char ch;
    bool EndLine = false;
    bool IsEof = false;

    Line->clear();
    do
    {
        mFs.get(ch);
        if (!mFs.eof())
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
            IsEof = true;
        }
    } while (!EndLine);

    return !IsEof;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO2
// Methode:   ReadSplitLine
//
//
//---------------------------------------------------------------------------

bool CFileIO2::ReadSplitLine(stringvector* SplitVector, char SplitChar, std::string* Line)
{
    bool r = false;

    if (SplitVector != NULL)
    {
        string LineBuffer;

        r = ReadLine(&LineBuffer);
        SplitVector->clear();
        NStringTool::Split(LineBuffer, SplitVector, SplitChar);
        if (Line != nullptr)
        {
            *Line = LineBuffer;
        }
    }
    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO (static)
// Methode:   ReadFile
//
// Parameter: char* Filename - Name der Datei
//
//            int* nBytes    - Anzahl der Bytes die gelesen wurden (Groesse
//                             der Datei).
//
// Return:    void* - Zeiger auf Puffer, in den die Daten gelesen wurden,
//                    oder NULL (Fehlerfall)
//
//
//
// Lesen des Inhalts einer Datei in einen Puffer. Der Speicher fuer den
// Puffer wird reserviert. Zurueckgegeben werden ein Zeiger auf den
// Puffer sowie die Anzahl der eingelesenen Bytes
//
//---------------------------------------------------------------------------

void* CFileIO2::ReadFile(const char* Filename, int* nBytes)
{
    char* buffer = NULL;

    *nBytes = CFileIO2::GetFileSize(Filename);
    if (*nBytes > 0)
    {
        fstream fs(Filename, ios::in | ios::binary);

        if (fs.good())
        {
            buffer = new char[*nBytes+1];
            if (buffer != NULL)
            {
                fs.read((char*)buffer, *nBytes);
                fs.close();
                buffer[*nBytes] = 0;
            }
        }
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO (static)
// Methode:   WriteFile
//
// Parameter: char* Filename - Name der Datei
//
//            int   nBytes    - Anzahl der Bytes die gelesen wurden (Groesse
//                             der Datei).
//
//            const void* - Zeiger auf Puffer, dessen Daten geschrieben
//                          werden
//
//
//---------------------------------------------------------------------------

bool CFileIO2::WriteFile(const char* Filename, const void* buffer, int nBytes)
{
    bool r = false;

    if (nBytes > 0)
    {
        fstream fs(Filename, ios::out | ios::binary);

        if (fs.good())
        {
            fs.write((const char*)buffer, nBytes);
            fs.close();

            r = true;
        }
    }
    return r;
}
