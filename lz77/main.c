#include <stdio.h>
#include <stdlib.h>

struct prefix
{
    char pos;
    char len;
};

struct prefix find_prefix(char * buf1, unsigned len1, char * buf2, unsigned len2)
{
    struct prefix best;
    best.pos = 0;
    best.len = 0;

    for(unsigned long i = 0; i<len2-len1; i++)
    {
        unsigned long j = 0;
        while(buf1[j] == buf2[i+j] && j<len1)
            j++;

        if(j > best.len)
        {
            best.len = j;
            best.pos = i;
        }
    }

    return best;
};

void insert_right(char * bufor, unsigned long len, char byte)
{
    unsigned long i = 0;

    while(i<len-1)
    {
        bufor[i] = bufor[i+1];
        i++;
    }

    bufor[i] = byte;
}

unsigned long lz77(char * in, unsigned long len, unsigned long dict, unsigned long buff, char * out)
{
    char * buforoslownik = (char*)malloc(sizeof(char)*(dict+buff));
    struct prefix trojka;

    unsigned long i = 0;
    while(i<dict)
    {
        buforoslownik[i] = in[0];
        i++;
    }
    while(i<dict+buff)
    {
        buforoslownik[i] = in[i-dict];
        i++;
    }
    i = dict;
    out[0] = in[0];
    unsigned long k = 1;
    unsigned long diff = 0;

    while(i<buff+dict && i<len+dict)
    {
        if(i>len)
            diff = i-len;
        trojka = find_prefix(buforoslownik+dict, buff-1-diff, buforoslownik, buff+dict-1-diff);
        out[k] = trojka.pos;
        out[k+1] = trojka.len;
        out[k+2] = buforoslownik[dict+trojka.len];
        k = k+3;
        for(unsigned long j = 0; j<trojka.len+1; j++)
        {
            insert_right(buforoslownik, buff+dict, in[i]);
            i++;
        }
    }

    i = i-dict-buff;

    diff = 0;
    while(i+dict<len)
    {
        if(i+buff+dict>len)
            diff = i+buff-(len+dict);
        trojka = find_prefix(in+i+dict, buff-diff-1, in+i, dict+buff-1-diff);
        out[k] = trojka.pos;
        out[k+1] = trojka.len;
        out[k+2] = in[i+dict+trojka.len];
        k = k+3;
        for(unsigned long j = 0; j<trojka.len+1; j++)
            i++;
    }

    return k;
}

unsigned long reverse_lz77(char * in, unsigned long len, unsigned long dict, unsigned long buff, char * out)
{
    unsigned long i = 0;
    while(i<dict)
    {
        out[i] = in[0];
        i++;
    }

    unsigned long k = 1;
    unsigned long j;
    while(k<len)
    {
        for(j = 0; j<in[k+1]; j++)
        {
            out[i+j] = out[i-dict+in[k]+(j%(dict-in[k]))];
        }
        i = i + j;
        out[i] = in[k+2];
        i++;
        k+=3;
    }

    return i;
}

int main()
{
    char data[13] = "aabbcabbcdddc";
    char out[256];
    char out2[256];

    unsigned long out_len = lz77(data, 13, 4, 4, out);

    printf("%d\n%c\n", out_len, out[0]);
    for(unsigned long i = 1; i<out_len; i = i+3)
        printf("%d %d %c\n", out[i], out[i+1], out[i+2]);

    unsigned long out2_len = reverse_lz77(out, out_len, 4, 4, out2);
    out2[out2_len] = 0;
    printf("%d\n", out2_len);
    printf("%s", out2+4);

    return 0;
}
