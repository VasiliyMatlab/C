#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void mysignal_handler(int);

int main(void) {
    int c = 0;

    // Задаем обработчик сигнала SIGINT
    signal(SIGINT, mysignal_handler);

    while (1) {
        printf("Hello, I'm here %d!\n", c++);
        usleep(1000000);
    }
    
    return 0;
}

// Обработчик сигнала SIGINT
void mysignal_handler(int signalno) {
    printf("Called with %d\n", signalno);
}