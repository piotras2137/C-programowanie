Struktury:
struct list
struct list_head

Funkcje:
struct list_head list_init()
1.Zwraca strukture list_head

unsigned char list_insert(struct list_head * list_head, void * value, unsigned int index)
1.Zwraca 0 jeśli zaalokowano pamięć na element listy
2.Zwraca 1 jeśli nie udało się alokować pamięci na element listy
3.Zwraca 2 jeśli lista nie może pomieścić następnego elementu
4.Zwraca 3 jeśli zakres listy został przekroczony

unsigned char list_delete(struct list_head * list_head, unsigned int index)
1.Zwraca 0 jeśli element został usunięty
2.Zwraca 1 jeśli element nie został usunięty

void * list_element(struct list_head list_head, unsigned int index)
1.Zwraca adres jeśli element istnieje
2.Zwraca 0 jeśli lista jest pusta

unsigned int list_count(struct list_head list_head)
1.Zwraca ilość elementów listy

Sposób użycia:

1.Tworzenie listy:
a)Deklaracja struktury list_head i inicjalizacja funkcją list_init
przykład:
struct list_head list_head = list_init();

2.Wrzucanie do listy:
Lista przechowuje dane 4-bajtowe, lista indeksuje elementy od 0 do list_head.counter-1
a)Inicjalizacja zmiennej o wybranym typie i wybranej wartości
b)Przekazanie adresu struktury queue_head, adresu zmiennej z wartością i indeksu w funkcji list_insert(struct list_head * list_head, void * value, unsigned int index)
Insert wstawia dany element na pozycję i, gdzie i to numer indeksu
dla i = 0 wstawia na początek listy
dla i od 1 do list_head.counter-1 na pozycję i, elementy o indeksie k > i stają się elementami o indeksie k+1
dla i = list_head.counter wstawia na koniec listy
przykład:
float x = 5.55;
list_insert(&list_head, &x, 0);

Możliwe jest również przechowanie danych <4-bajtowych poprzez rzutowanie ich na zmienną 4-bajtową.

3.Usuwanie z listy
a)Przekazanie adresu struktury struct list_head i indeksu w funkcji unsigned char list_delete(struct list_head * list_head, unsigned int index)
przykład:
list_delete(&list_head, 1);

4.Pobieranie danej z elementu
Lista zwraca adres zmiennej gdzie jest dana, należy go rzutować na wskaźnik 4-bajtowy i wyłuskać.
a)Przekazanie struktury struct list_head i indeksu w funkcji list_element(struct list_head list_head, unsigned int index)
b)Rzutowanie na 4-bajtowy wskaźnik
c)Wyłuskanie
przykład:
*(float*)list_element(list_head, a)

5.Pobieranie ilości elementów list_count(struct list_head list_head)
a)Przekazanie struktury struct list_head w funkcji 
przykład:
list_count(list_head);