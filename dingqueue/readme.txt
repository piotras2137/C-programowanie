Struktury:
struct queue - element kolejki
struct queue_head - kolejka

Funkcje:
struct queue_head queue_init()
1.Zwraca strukture queue_head

unsigned char queue_push(struct queue_head * queue_head, void * value)
1.Zwraca 0 jeśli zaalokowano pamięć na element kolejki
2.Zwraca 1 jeśli nie udało się alokować pamięci na element kolejki
3.Zwraca 2 jeśli kolejka nie może pomieścić następnego elementu

unsigned char queue_pop(struct queue_head * queue_head)
1.Zwraca 0 jeśli element został usunięty
2.Zwraca 1 jeśli element nie został usunięty

void * queue_first(struct queue_head queue_head)
1.Zwraca adres jeśli element istnieje
2.Zwraca 0 jeśli kolejka jest pusta

unsigned char queue_empty(struct queue_head queue_head)
1.Zwraca 0 jeśli kolejka nie jest pusta
2.Zwraca 1 jeśli kolejka jest pusta

Sposób użycia

1.Tworzenie kolejki:
a)Deklaracja struktury queue_head i inicjalizacja funkcją queue_init
przykład:
struct queue_head queue_head = queue_init();

2.Wrzucanie do kolejki:
kolejka przechowuje dane 4-bajtowe
a)Inicjalizacja zmiennej o wybranym typie i wybranej wartości
b)Przekazanie adresu struktury queue_head i adresu zmiennej z wartością w funkcji queue_push(struct queue_head * queue_head, void * value)
przykład:
float x = 45.45;
queue_push(&queue_head, &x);

Możliwe jest również przechowanie danych <4-bajtowych poprzez rzutowanie ich na zmienną 4-bajtową.

3.Usuwanie z kolejki
a)Przekazanie adresu struktury struct queue_head w funkcji queue_pop(struct queue_head * queue_head)
przykład:
queue_pop(&queue_head);

4.Pobieranie przechowywanej danej z kolejki
Kolejka zwraca adres zmiennej gdzie jest dana, należy go rzutować na wskaźnik 4-bajtowy i wyłuskać.
a)Przekazanie struktury struct queue_head w funkcji queue_first(struct queue_head queue_head)
b)Rzutowanie na 4-bajtowy wskaźnik
c)Wyłuskanie
przykład:
*(float*)queue_top(queue_head);

5.Sprawdzanie czy kolejka zawiera jakieś dane
a)Przekazanie struktury struct queue_head w funkcji queue_empty(struct queue_head queue_head)
przykład:
queue_empty(queue_head);