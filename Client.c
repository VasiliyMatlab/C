#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Пример создания клиентского приложения, которое
// подключается к серверу по протоколам TCP и IPv4
// Использовать в сочетании с bash-скриптом '_client-server.sh'
int main(void) {
    int status;
    srand(time(NULL));

    // Создаем сокет
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Задаем адрес
    char servaddr[] = "127.0.0.1";
    int servport = 3453;
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(servport);
    status = inet_pton(AF_INET, servaddr, &addr.sin_addr);
    if (status == 0) {
        fprintf(stderr, "inet_pton failed: src does not contain a character"
                " string representing a valid network address in the specified"
                " address family\n");
        exit(EXIT_FAILURE);
    }
    if (status == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Подключаемся к сокету
    status = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
    if (status == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server %s:%d\n", servaddr, servport);

    // Цикл передачи сообщений с приемом подтверждения от сервера
    char buf[BUFSIZ];
    ssize_t bytes;
    int count = rand() % 18 + 2; // Кол-во посылаемых сообщений
    printf("Number of messages: %d\n", count);
    while (count) {
        // Формирование сообщения
        memset(buf, 0, BUFSIZ);
        int len = rand() % 40 + 1;
        for (int i = 0; i < len; i++)
            buf[i] = rand() % 95 + 32;
        // Передаем информацию на сервер
        bytes = write(sock, buf, BUFSIZ);
        printf("[%d] Message sent\t (%ld bytes):\t%s\n", getpid(), strlen(buf), buf);
        // Получаем информацию от сервера
        memset(buf, 0, BUFSIZ);
        bytes = read(sock, buf, BUFSIZ);
        if (bytes == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (bytes == 0) {
            printf("EOF occured\n");
            break;
        }
        printf("[%d] Message recieved (%ld bytes):\t%s\n", getpid(), strlen(buf), buf);
        sleep(1);
        count--;
    }

    // Закрываем сокет
    printf("Closing connecton\n");
    close(sock);

    return 0;
}