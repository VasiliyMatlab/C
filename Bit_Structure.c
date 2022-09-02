#include <stdio.h>
#include <stdint.h>

typedef struct bytes {
    uint8_t a0: 1;
    uint8_t a1: 2;
    uint8_t a2: 4;  // <-- поле занимает 4 бита, можно использовать числа от 0 до 15
    uint8_t   : 0;  /* <-- неименованное поле нулевого размера 
                           следующее за ним поле смещается на границу 8 бит
                           если адрес поля уже кратен 8 битам, то нулевое поле не добавляет сдвига*/
    uint8_t a4: 3;
    uint8_t a5: 1;
    uint8_t a6: 1;
    uint8_t a7: 1;
} bytes_t;

// Пример использования битовых структур (полей)
int main (void) {
    //          a0 a1  a2 a4 a5 a6 a7
    bytes_t x = {0, 3, 12, 1, 0, 1, 0};
    printf("sizeof byte_t = %u bytes\n", sizeof(bytes_t));
    printf("a0 = %u\n", x.a0);
    printf("a1 = %u\n", x.a1);
    printf("a2 = %u\n", x.a2);
    //printf("a3 = %u\n", x.a3);
    printf("a4 = %u\n", x.a4);
    printf("a5 = %u\n", x.a5);
    printf("a6 = %u\n", x.a6);
    printf("a7 = %u\n", x.a7);
    return 0;
}
