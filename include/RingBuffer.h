#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stdint.h>

#define CAPACITY 4
#define RINGBUFFER_FULL     1
#define RINGBUFFER_EMPTY    2

typedef struct ring_buffer {
    uint8_t in;
    uint8_t out;
    uint8_t *buffer;
} ring_buffer_t;

ring_buffer_t *init_ring_buffer(void);
void clear_ring_buffer(ring_buffer_t *);

void print_ring_buffer(const ring_buffer_t *);
int push_to_ring_buffer(ring_buffer_t *, const uint8_t);
int pop_from_ring_buffer(ring_buffer_t *, uint8_t *);

#endif /* _RING_BUFFER_H_ */
