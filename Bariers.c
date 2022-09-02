#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define ERROR_CREATE_THREAD   -11
#define ERROR_JOIN_THREAD     -12
#define BAD_MESSAGE           -13
#define ERROR_INIT_BARRIER    -14
#define ERROR_WAIT_BARRIER    -15
#define ERROR_DESTROY_BARRIER -16
#define SUCCESS                 0
#define NUM_THREADS             4

// Структура для передачи данных в потоки
typedef struct someArgs_tag {
    int id;
    const char *msg;
    int out;
    pthread_barrier_t *bar;
} someArgs_t;

// Функция потоков
void *helloWorld(void *);

// Пример работы с барьерами,
// позволяющими синхронизировать потоки
// в определенной точке
int main(){
    // Объявление переменных
    pthread_t threads[NUM_THREADS];
    int status;
    int i;
    int status_addr;
    someArgs_t args[NUM_THREADS];
    const char *messages[] = {
        "First",
        NULL,
        "Third Message",
        "Fourth Message"
    };
    pthread_barrier_t barrier;

    // Заполнение струтур данными
    for (i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].msg = messages[i];
        args[i].bar = &barrier;
    }

    // Инициализация барьера
    status = pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1);
    if (status != 0) {
        printf("main error: can't init barrier, status = %d\n", status);
        exit(ERROR_INIT_BARRIER);
    }

    // Создание потоков
    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
        if (status != 0) {
            printf("main error: can't create thread, status = %d\n", status);
            exit(ERROR_CREATE_THREAD);
        }
    }
    printf("Main Message\n");

    // Синхронизация потоков
    status = pthread_barrier_wait(&barrier);
    if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
        pthread_barrier_destroy(&barrier);  // разрушение барьера
    } else if (status != 0) {
        printf("error wait barrier in main thread with status = %d\n", status);
        exit(ERROR_WAIT_BARRIER);
    }

    // Вывод результатов обработки
    for (i = 0; i < NUM_THREADS; i++) {
        printf("thread %d arg.out = %d\n", i, args[i].out);
    }
    return 0;
}

// Функция потоков
void *helloWorld(void *args) {
    someArgs_t *arg = (someArgs_t*) args;
    int id = arg->id;
    int len;
    int status;
    int retVal;

    // Основная обработка функции
    if (arg->msg == NULL) {
        retVal = BAD_MESSAGE;
    } else {
        len = strlen(arg->msg);
        printf("%s\n", arg->msg);
        arg->out = len;
        retVal = SUCCESS;
    }

    // Синхронизация потоков
    status = pthread_barrier_wait(arg->bar);
    if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
        pthread_barrier_destroy(arg->bar);  // разрушение барьера
    } else if (status != 0) {
        printf("error wait barrier in thread %d with status = %d\n", arg->id, status);
        exit(ERROR_WAIT_BARRIER);
    }
    return retVal;
}
