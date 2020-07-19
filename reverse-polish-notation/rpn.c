#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

///definicje do programu
///definicja czy dany znak jest spacja
#define spacja(x) (x==' ')

///tutaj są definicje do znakow matematycznych 
#define znak(x) (x=='+' || x=='-' || x=='=' || x=='/' || x=='*' || x=='^' )
#define minus(x) (x=='-')
///definicja czy jest rowne
#define tosamo(x,y) (x==y)
///definicje do nawiasow
#define otwarty(x) (x=='(')
#define zamkniety(x) (x==')')
#define nawias(x) (otwarty(x) || zamkniety(x))
///definicje czy jest to koniec pliku 
#define eol(x) (x=='\n')
///definicja czy dany znak jest cyfra
#define liczba(x) (x<=57 && x>=48)

///takie przyspieszenie
typedef FILE* plik;

////struktura listy uzywana pozniej 
struct list
{
    int val;
    struct list *next;
};

///funkcja do dodania elementu do listy
void ddl(struct list *lista, int wartosc)
{
    struct list *wsk=lista, *nowy;
    
    while(wsk->next!=NULL)
        wsk=wsk->next;
    
    nowy=malloc(sizeof(struct list));
    nowy->val=wartosc;
    nowy->next=NULL;

    wsk->next=nowy;

}

///funkcja do robienia obliczen
int calc(int val1, int val2, char sign)
{
    switch(sign)
    {
        case '+':///dodawanie
        return val1+val2;

        case '-':///odejmowanie
        return val1-val2;

        case '/':///dzielenie
        return val1/val2;

        case '*':///mnozenie
        return val1*val2;

        case '=':///sprawdzanie czy liczby są rowne 
        return val1*tosamo(val1,val2);

        case '^':///potegowanie
        return pow(val1,val2);

        case '%':///modulo 
        return val1%val2;
                
    }
    return 0;
}

///funkcja do odwrotnej notacji polskiej 
int rpn(char napis[], int dlugosc)///podajemy ciag znakow zawierajacy wyrazenie i jego dlugosc
{
    ///definicja struktory(na liczby)
    struct list *lista;
    lista=malloc(sizeof(struct list));
    lista->next=NULL;
    int dl=0;///zmienna na dlugosc tej listy 
    
    int wynik=0;///zmienna na wynik
    int val=0;///zmienna na wartosci odczytywane z wyrazenia

    for(int i=0; i<dlugosc;i+=1)///glowna pentla
    {
        if(spacja(napis[i]) && val!=0)///sprawdzenie czy aktualny znak jest spacja i czy jest jakas wartosc w bufferze 
        {
            ///dodawanie elementow do listy
            if(dl==0)
            {
                lista->val=val;
                dl+=1;
                val=0;
            }
            else
            {
                ddl(lista,val);
                dl+=1;
                val=0;
            }
            
        }
        ///dodanie liczb ujemnych 
        if(minus(napis[i]) && val!=0)
        {
            val*=-1;
        }
        ///robienie liczb z cyfr z tekstu
        if(liczba(napis[i]))
        {
            if(val==0)
            {
                val=napis[i]-48;
            }
            else
            {
                val*=10;
                val+=napis[i]-48;
            }
            
        }
        if(znak(napis[i]))///jezeli mamy znak(ten matematyczny) to wykonuje sie operacja liczenia widoczna na dole
        {
            while(lista->next!=NULL)
            {
                struct list *l2;
                l2=lista->next;
                lista->val=calc(lista->val,l2->val,napis[i]);
                lista->next=l2->next;
                free(l2);
            }
        }
        if(nawias(napis[i]))///obsluga nawiasow 
        {
            if(zamkniety(napis[i]))
            {
                break;
            }
            if(otwarty(napis[i]))
            {
                i+=1;
                int nd=dlugosc-i, in=1;
                char nn[nd];
                
                for(int j=0; j<nd;j+=1)
                    nn[j]=napis[i+j];
                
                if(dl>0)
                {
                    ddl(lista,rpn(nn,nd));
                    dl+=1;
                }
                else
                {
                    lista->val=rpn(nn,nd);
                    dl+=1;
                }

                while(in>0)
                {
                    if(otwarty(napis[i]))
                        in+=1;
                    if(zamkniety(napis[i]))
                        in-=1;

                    i+=1;
                }
            }
        }
    }

////jak widac zmienna wynik jest niepotrzebna :-<
    return lista->val;
}



void odczyt(char *nazwapliku)///funkcja obslugujaca pliki i rpn z nich  
{
    plik kek;
    char literka[100];
    ///tutaj sprawdzenie czy da sie otworzyc
    if((kek=fopen(nazwapliku,"r"))==NULL)
    {
        printf("nie udało sie odczytac pliku");
        exit(0);
    }
    else
    {
        ///samo dzialanie 
        while(fgets(literka,100,kek))
        {
            printf("%d",rpn(literka,strlen(literka)));
        }
    }
    
}

int main()
{
    ///char napis[]="2 2 ^";
    ///printf("%d",rpn(napis,strlen(napis)));
    char *nazwapliku="rpn.txt";
    odczyt(nazwapliku);
    return 0;
}
