#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *a, void *b, size_t size);
void print_struct(void *k);

struct Example {
    float a;
    double c;
    unsigned long e;
};

// Пример работы с переменными, завернутыми в void *
int main(void) {
    float a = 10.f;
    float b = 20.f;
    double c = 555;
    double d = 777;
    unsigned long e = 2ll;
    unsigned long f = 3ll;
 
    printf("a = %.3f, b = %.3f\n", a, b);
    swap(&a, &b, sizeof(float));
    printf("a = %.3f, b = %.3f\n", a, b);
 
    printf("c = %.3f, d = %.3f\n", c, d);
    swap(&c, &d, sizeof(double));
    printf("c = %.3f, d = %.3f\n", c, d);
 
    printf("e = %ld, f = %ld \n", e, f);
    swap(&e, &f, sizeof(unsigned long));
    printf("e = %ld, f = %ld \n", e, f);

    struct Example test;
    test.a = a;
    test.c = c;
    test.e = e;
    print_struct(&test);

    return 0;
}

// Обмен содержимого двух переменных
void swap(void *a, void *b, size_t size) {
    char *tmp;
    //создаём временную переменную для обмена
    tmp = (char *) malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

// Вывести на экран структуру
void print_struct(void *k) {
    printf("Structure Example:\n");
    printf("a = %.3f\n", ((struct Example *) k)->a);
    printf("a = %.3f\n", ((struct Example *) k)->c);
    printf("a = %ld\n", ((struct Example *) k)->e);
}
