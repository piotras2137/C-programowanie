#ifndef NUMCON_H_INCLUDED
#define NUMCON_H_INCLUDED

void convert(int liczba, int sys)
{
    int power=0;
    while(liczba>pow(sys,power))
    {
        power+=1;
    }
    int tabela[power];
    int pozycja=power-1;
    while(liczba>0)
    {
        tabela[pozycja]=liczba%sys;
        liczba=liczba/sys;
        pozycja-=1;
    }
    for(int i=0; i<power; ++i)
    {
        if(tabela[i]>9)
        {
            switch(tabela[i])
            {
            case 10:
                printf("A");
            case 11:
                printf("B");
            case 12:
                printf("C");
            case 13:
                printf("D");
            case 14:
                printf("E");
            case 15:
                printf("F");
            }
        }
        else
        {
            printf("%d",tabela[i]);
        }
    }
}
///taka pomocnicza funkcyjka która pózniej sie przyda
void c2b(char letter)
{
    convert(letter);
}
#endif // NUMCON_H_INCLUDED
