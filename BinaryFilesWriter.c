#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <endian.h>

#define SIZE    7

uint16_t data[SIZE] = {
    0xF026,
    0x1220,
    0xF026,
    0x1240,
    0x1060,
    0xF027,
    0xF025
};

// Запись бинарного файла
int main(void) {
    // Открываем файл на чтение
    char *filename = "filebin.obj";
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "Cannot write to file %s\n", filename);
        return 1;
    }

    // Преобразуем порядок байт в BigEndian
    for (int i = 0; i < SIZE; i++)
        data[i] = htobe16(data[i]);

    // Записываем данные
    size_t bytes = fwrite(data, sizeof(uint16_t), sizeof(data), f);
    fprintf(stdout, "Written size_t = %lu to file %s\n", bytes, filename);
    
    // Закрываем файл
    fclose(f);
    return 0;
}