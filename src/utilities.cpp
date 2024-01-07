#include "utilities.h"

char *i2str(int i, char *buf)
{
    unsigned char l = 0;
    if (i < 0)
        buf[l++] = '-';
    bool leadingZ = true;
    for (int div = 10000, mod = 0; div > 0; div /= 10)
    {
        mod = i % div;
        i /= div;
        if (!leadingZ || i != 0)
        {
            leadingZ = false;
            buf[l++] = i + '0';
        }
        i = mod;
    }
    buf[l] = 0;
    return buf;
}