#ifndef CHEXCONV
#define CHEXCONV

class CHexConv
{
    public:

        static int NibbleToInt(char a);
        static int ByteToInt(unsigned char a, unsigned char b);
        static float ByteToFloat(unsigned char a, unsigned char b);
        static int StringToInt(const char* s);
        static std::string ToHex(int i);
};

#include <CHexConv.hpp>

#endif // CHEXCONV
