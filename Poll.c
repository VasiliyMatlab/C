#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

// Пример работы с системным вызовом poll
int main(void) {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5555);
    bind(sock, &servaddr, sizeof(servaddr));

    // Параметры отправителя
    static struct sockaddr_in clnt_src = {0};
    static socklen_t clnt_src_len = sizeof(clnt_src);

    // Инициализация структуры и ее полей
    struct pollfd pfds = {0};
    pfds.fd = sock;
    pfds.events = POLLIN;

    // Цикл считывания данных
    while (1) {
        int ready;
        // Ожидаем изменения состояния сокета в течение 1 с
        ready = poll(&pfds, 1, 1000);
        if (ready == -1) {
            printf("Error\n");
            continue;
        }
        if (ready == 0) {
            printf("Timeout\n");
            continue;
        }
        // Если поступили данные на вход, то считаем их
        if (pfds.revents & POLLIN) {
            ssize_t bytes;
            char *buf[32];
            bytes = recvfrom(sock, buf, 31, 0, &clnt_src, &clnt_src_len);
            printf("Received %d bytes: %s", bytes, buf);
        }
    }

    close(sock);
    return 0;
}