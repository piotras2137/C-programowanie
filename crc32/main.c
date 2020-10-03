#include <stdio.h>
#include <stdlib.h>

#define polynomial 0xEDB88320

void make_crc32_table(unsigned long * tab32)
{
    unsigned long crc;
    for(unsigned long i = 0; i<256; i++)
    {
        crc = i;
        for(unsigned long j = 0; j<8; j++)
        {
            if(crc&0x1)
            {
                crc = crc>>1;
                crc = crc^polynomial;
            }
            else
                crc = crc>>1;
        }
        tab32[i] = crc;
    }

    return;
}

unsigned long crc32(char * buff, unsigned long len, unsigned long * tab)
{
    unsigned long crc = 0xFFFFFFFF;

    for(unsigned long i = 0; i<len; i++)
    {
        crc = crc^buff[i];
        crc = (crc >> 8)^(tab[crc&0xFF]);
    }

    return ~crc;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
