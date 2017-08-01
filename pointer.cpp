// Пример передачи данных по указателю (*) и по указателю на указатель (**).

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h> 

void foo1(int *p) {
// Указатель передаётся по значению (копия указателя создаётся на стеке) после выхода из функции указатель теряется.
    p = (int*)malloc(80);
    printf("%p\n", p);
    *p = 101;
}

void foo2(int **p) {
// Указатель на указатель передаётся по значению (копия указателя на указатель создаётся на стеке).
    // Разыменовав указатель на указатель, получим значение = адресу переданного элемента, а в эту функцию передаётся указатель на int.    
    *p = (int*)malloc(80);
    printf("%p\n", *p);
    **p=101;
}

void test1(void) {
    int p=7;
    int *k = &p;
    printf("%p\n", k);
    foo1(k);
    printf("%p\n", k);
    printf("%d\n", *k);
}

void test2(void) {
    int p=7;
    int *k = &p;
    printf("%p\n", k);
    foo2(&k);
    printf("%p\n", k);
    printf("%d\n", *k);
}

int main() {
    test1();
    printf("\n");
    test2();
    return 0;
}

/* Результат:

0x769eceae4e6c
0x1df8af0
0x769eceae4e6c
7

0x769eceae4e64
0x1df8b50
0x1df8b50
101

*/
