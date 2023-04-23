#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Пример работы с получением информации о сети
// Для более наглядного примера следует использовать совместно
// с bash-скриптом '_show_ip.sh'
int main(int argc, char *argv[]) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
    // AF_INET или AF_INET6 в случае определенной версии протокола IP
    // Если неважно, то AF_UNSPEC
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM; // протокол TCP (если UDP - SOCK_DGRAM)
    // Результат записывается в 'res' в виде связанного списка
    // номер порта - NULL (не важен)
    status = getaddrinfo(argv[1], NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("IP addresses for %s:\n", argv[1]);
    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        
        // Если IPv4
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        // Если IPv6
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        // Перевод адресса IP 'addr' в строку 'ipstr'
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s: %s\n", ipver, ipstr);
    }

    // Освобождение связанного списка
    freeaddrinfo(res);
    return 0;
}