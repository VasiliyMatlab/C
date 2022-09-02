#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void read_and_report(int);

int main() {
    // Создаем два именованных канала
    int f1 = open("./f1.fifo", O_RDWR);
    int f2 = open("./f2.fifo", O_RDWR);
    if ((f1 == -1) || (f2 == -1)) {
        fprintf(stderr, "Error with opening pipes\n");
        return -1;
    }

    printf("Descriptors: %d %d\n", f1, f2);

    // Задаем время опроса
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    fd_set read_set;

    while (1) {
        // Обнуляем маску
        FD_ZERO(&read_set);
        // Устанавливаем наблюдение за дескриптором f1
        FD_SET(f1, &read_set);
        // Устанавливаем наблюдение за дескриптором f2
        FD_SET(f2, &read_set);
        // Ищем наибольший номер дескриптора и увеличиваем на единицу
        int largest_fd = (f1 > f2) ? f1+1 : f2+1;
        // Осуществляем наблюдение за каналами
        // вторая версия для наблюдения в течение какого-либо времени
        int result = select(largest_fd, &read_set, NULL, NULL, NULL);
        //int result = select(largest_fd, &read_set, NULL, NULL, &timeout);
        printf("select returned %d\n", result);

        switch (result) {
            case -1:
                fprintf(stderr, "Error\n");
                exit(-1);
                break;
            case 0:
                fprintf(stderr, "Timeout error\n");
                exit(-1);
                break;
            default:
                // Проверяем первый дескриптор
                if(FD_ISSET(f1, &read_set))
                    read_and_report(f1);
                // Проверяем второй дискриптор
                if(FD_ISSET(f2, &read_set))
                    read_and_report(f2);
        }
    }
    
    if ((close(f1) == -1) || (close(f2) == -1)) {
        fprintf(stderr, "Error with closing pipes\n");
        exit(-1);
    }
    return 0;
}

void read_and_report(int fd) {
    printf("FD %d is ready to read\n", fd);
    char buf[BUFSIZ];
    // Читаем в буфер данные из канала
    // bytes - кол-во прочитанных байт
    int bytes = read(fd, buf, BUFSIZ-1);
    // Устанавливаем последний элемент в нуль
    buf[bytes] = 0;
    printf("Get %d bytes from %d : %s\n", bytes, fd, buf);
}