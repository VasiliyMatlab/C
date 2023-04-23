#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define UNSIGNED_OVERFLOW -4

unsigned summ(unsigned num, ...) {
    // Переменная типа va_list – список аргументов
    va_list args;
    unsigned sum = 0;
    unsigned testsum = 0;
    // Устанавливаем указатель на первый элемент
    va_start(args, num);
     
    while (num--) {
        // Достаём следующий, указывая тип аргумента
        testsum += va_arg(args, unsigned);
        if (testsum >= sum) {
            sum = testsum;
        } else {
            exit(UNSIGNED_OVERFLOW);
        }
    }
 
    va_end(args);
    return sum;
}

// Пример работы с функциями,
// принимающими переменное число параметров
int main(void) {
    int sum = summ(5u, 1u, 2u, 3u, 4u, 5u);
    printf("summ = %u\n", sum);
    sum = summ(7u, 0u, 27u, 0u, 4u, 5u, 60u, 33u);
    printf("summ = %u\n", sum);
    return 0;
}
