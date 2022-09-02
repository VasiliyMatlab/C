#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t data[] = {
    0xF026,
    0x1220,
    0xF026,
    0x1240,
    0x1060,
    0xF027,
    0xF025
};

int main() {
    char *filename = "filebin.obj";
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "Cannot write to file %s\n", filename);
        return 1;
    }
    size_t bytes = fwrite(data, sizeof(uint16_t), sizeof(data), f);
    fprintf(stdout, "Written size_t = %lu to file %s\n", bytes, filename);
    fclose(f);
    return 0;
}