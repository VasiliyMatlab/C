#include "include/RingBuffer.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

ring_buffer_t *init_ring_buffer(void) {
    ring_buffer_t *ptr = (ring_buffer_t *) malloc(sizeof(ring_buffer_t));
    ptr->in = 0;
    ptr->out = 0;
    ptr->buffer = (uint8_t *) malloc(CAPACITY*sizeof(uint8_t));
    return ptr;
}

void clear_ring_buffer(ring_buffer_t *ptr) {
    free(ptr->buffer);
    free(ptr);
}

void print_ring_buffer(const ring_buffer_t *ptr) {
    printf("******************************\n");
    printf("ptr\n");
    printf(" |--in  = %u\n", ptr->in);
    printf(" |--out = %u\n", ptr->out);
    printf(" +--buffer = [");
    for (uint8_t i = 0; i < CAPACITY; i++) {
        printf("%u, ", ptr->buffer[i]);
    }
    printf("\b\b \b]\n");
    printf("******************************\n");
}

int push_to_ring_buffer(ring_buffer_t *ptr, const uint8_t val) {
    ptr->buffer[ptr->in++] = val;
    ptr->in %= CAPACITY;
    if (ptr->in == ptr->out) {
        ptr->buffer[ptr->out++] = 0;
        ptr->out %= CAPACITY;
    }
    return 0;
}

int pop_from_ring_buffer(ring_buffer_t *ptr, uint8_t *val) {
    if (ptr->in == ptr->out) {
        return -RINGBUFFER_EMPTY;
    }
    *val = ptr->buffer[ptr->out];
    ptr->buffer[ptr->out++] = 0;
    ptr->out %= CAPACITY;
    return 0;
}
