#ifndef CFILEIO2_H
#define CFILEIO2_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <NStringTool.h>

#define OPENMODE	std::ios_base::openmode
#define SEEKDIR		std::ios_base::seekdir



class CFileIO2
{
    public:

        CFileIO2();

        bool OpenFileRead(const char* Filename, OPENMODE type);
        bool OpenFileWrite(const char* Filename, OPENMODE type);
        bool ReadBytes(void* buffer, int nBytes);
        bool WriteBytes(const void* buffer, int nBytes);
        bool WriteString(const char* str);
        void CloseFile();
        bool ReadSplitLine(stringvector* SplitVector, char SplitChar, std::string* Line = nullptr);
        bool ReadLine(std::string* Line);
        void*  ReadFile(const char* Filename, int* nBytes);
        bool WriteFile(const char* Filename, const void* buffer, int nBytes);

        static long GetFileSize(const char* Filename);
        static void* ReadFile(const char* Filename, long* nBytes);

    protected:

        std::fstream mFs;

        bool mOpenRead;
        bool mOpenWrite;
};

#endif
