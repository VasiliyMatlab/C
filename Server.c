#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Пример создания сервера на протоколах TCP и IPv4
// Использовать в сочетании с bash-скриптом '_client-server.sh'
int main(void) {
    int status;
    ssize_t bytes;
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);

    // Создаем сокет
    int client;
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Создаем адрес
    int servport = 3453;
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(servport);
    socklen_t adrlen = sizeof(server_addr);

    // Привязываем адрес к сокету
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    status = bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (status == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Слушаем сокет
    status = listen(server, 5);
    if (status == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Цикл приема клиентов
    while (1) {
        // Принимаем клиента
        struct sockaddr_in client_addr = {0};
        client = accept(server, (struct sockaddr *) &client_addr, &adrlen);
        if (client == -1) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        char addr[256];
        int port;
        inet_ntop(AF_INET, &client_addr.sin_addr, addr, 256);
        if (addr == NULL) {
            perror("inet_ntop failed");
            exit(EXIT_FAILURE);
        }
        port = ntohs(client_addr.sin_port);
        printf("\nClient %s:%d accepted\n", addr, port);

        // Цикл приема сообщений с подтверждением
        while (1) {
            // Считываем сообщение клиента
            bytes = read(client, buf, BUFSIZ);
            if (bytes == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            if (bytes == 0) {
                printf("EOF occured\n");
                printf("Closing connection with client %s:%d\n", addr, port);
                close(client);
                break;
            }
            printf("[%d] Message received (%ld bytes):\t%s\n", getpid(), strlen(buf), buf);
            // Передаем ответ клиенту
            sleep(1);
            write(client, buf, bytes);
            printf("[%d] Message sent\t (%ld bytes):\t%s\n", getpid(), strlen(buf), buf);
        }
    }

    // Закрываем сокеты
    sleep(1);
    printf("Closing the server\n");
    close(client);
    close(server);

    return 0;
}