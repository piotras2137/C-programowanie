Struktury:
struct stack - element stosu
struct stack_head - stos

Funkcje:
struct stack_head stack_init()
1.Zwraca strukture stack_head

unsigned char stack_push(struct stack_head * stack_head, void * value)
1.Zwraca 0 jeśli wszystko przebiegło poprawnie
2.Zwraca 1 jeśli nie udało się alokować pamięci na element stosu
3.Zwraca 2 jeśli stos nie może pomieścić następnego elementu

unsigned char stack_pop(struct stack_head * stack_head)
1.Zwraca 0 jeśli element został usunięty
2.Zwraca 1 jeśli element nie został usunięty

void * stack_top(struct stack_head stack_head)
1.Zwraca adres jeśli element istnieje
2.Zwraca 0 jeśli stos jest pusty

unsigned char stack_empty(struct stack_head stack_head)
1.Zwraca 0 jeśli stos nie jest pusty
2.Zwraca 1 jeśli stos jest pusty

Sposób użycia:

1.Tworzenie stosu:
a)Deklaracja struktury stack_head i inicjalizacja funkcją stack_init
przykład:
struct stack_head stack_head = stack_init();

2.Wrzucanie na stos:
Stos przechowuje dane 4-bajtowe
a)Inicjalizacja zmiennej o wybranym typie i wybranej wartości
b)Przekazanie adresu struktury stack_head i adresu zmiennej z wartością w funkcji stack_push(struct stack_head * stack_head, void * value)
przykład:
float x = 64.5;
stack_push(&stack_head, &x);

Możliwe jest również przechowanie danych <4-bajtowych poprzez rzutowanie ich na zmienną 4-bajtową.

3.Usuwanie ze stosu
a)Przekazanie adresu struktury struct stack_head w funkcji stack_pop(struct stack_head * stack_head)
przykład:
stack_pop(&stack_head);

4.Pobieranie przechowywanej danej ze stosu
Stos zwraca adres zmiennej gdzie jest dana, należy go rzutować na wskaźnik 4-bajtowy i wyłuskać.
a)Przekazanie struktury struct stack_head w funkcji stack_top(struct stack_head stack_head)
b)Rzutowanie na 4-bajtowy wskaźnik
c)Wyłuskanie
przykład:
*(float*)stack_top(stack_head);

5.Sprawdzanie czy stos zawiera jakieś dane
a)Przekazanie struktury struct stack_head w funkcji stack_empty(struct stack_head stack_head)
przykład:
stack_empty(stack_head);