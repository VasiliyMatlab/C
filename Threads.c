#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12

// Потоковая функция
void *helloWorld(void *args) {
    printf("Hello from thread!\n");
    pthread_exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

// Пример работы программы с потоками
int main(void) {
    pthread_t thread;
    int status;
    int status_addr;
    
    // Создаем поток
    status = pthread_create(&thread, NULL, helloWorld, NULL);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(ERROR_CREATE_THREAD);
    }

    printf("Hello from main!\n");

    // Ждем завершения потока
    status = pthread_join(thread, (void**)&status_addr);
    if (status != EXIT_SUCCESS) {
        printf("main error: can't join thread, status = %d\n", status);
        exit(ERROR_JOIN_THREAD);
    }

    printf("joined with address %d\n", status_addr);
    
    return 0;
}