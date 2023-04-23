#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "include/RingBuffer.h"

// Пример использования кольцевого буфера
// Команда "push <num>" помещает число <num> в буфер
// Команда "pop" извлекает число из буфера
// Команда "exit" очищает буфер и завершает выполнение программы
int main(void) {
    ring_buffer_t *ring = init_ring_buffer();
    char buf[8];
    char num[3];
    print_ring_buffer(ring);
    while (true) {
        memset(buf, 0, 8);
        memset(num, 0, 3);
        scanf("%s", buf);
        if (buf[1] == 'u') {
            uint8_t tmp;
            scanf("%u", &tmp);
            int st = push_to_ring_buffer(ring, (const uint8_t) tmp);
            if (st == -RINGBUFFER_FULL) {
                printf("Error: Buffer is already full\n");
                continue;
            }
            print_ring_buffer(ring);
        } else if (buf[1] == 'o') {
            uint8_t tmp;
            int st = pop_from_ring_buffer(ring, &tmp);
            if (st == -RINGBUFFER_EMPTY) {
                printf("Error: Buffer is empty\n");
                continue;
            }
            printf("val = %u\n", tmp);
            print_ring_buffer(ring);
        } else if (buf[0] == 'e') {
            print_ring_buffer(ring);
            break;
        } else {
            printf("Error: Invalid command %s\n", buf);
        }
    }
    clear_ring_buffer(ring);
    return 0;
}
