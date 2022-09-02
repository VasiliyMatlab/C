#include <stdio.h>

void dbleInt(void *a) {
    *((int*) a) *= 2;
}

void deleteEvenInt(void* a) {
    int tmp = *((int*) a);
    if (tmp % 2 == 0) {
        *((int*) a) = 0;
    }
}

void dbleDouble(void *a) {
    *((double*) a) *= 2.0;
}

void deleteEvenDouble(void* a) {
    int tmp = *((double*) a);
    if (tmp % 2 == 0) {
        *((double*) a) = 0;
    }
}

//Функция принимает массив, его размер, размер одного элемента и указатель на функцию,
//которая далее применяется ко всем элементам массива
void map(void *arr, unsigned num, size_t size, void (*fun)(void *)) {
    unsigned i;
    char *ptr = (char*) arr;
    for (i = 0; i < num; i++) {
        fun((void*) (ptr + i*size));
    }
}

// Пример работы с указателями на функции
int main () {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double b[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
    unsigned i;
    //Работаем с массивом типа int
    map(a, 10, sizeof(int), deleteEvenInt);
    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    map(a, 10, sizeof(int), dbleInt);
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    //Работаем с массивом типа double
    map(b, 10, sizeof(double), deleteEvenDouble);
    for (i = 0; i < 10; i++) {
        printf("%.3f ", b[i]);
    }
    map(b, 10, sizeof(double), dbleDouble);
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%.3f ", b[i]);
    }
    printf("\n");
    return 0;
}
