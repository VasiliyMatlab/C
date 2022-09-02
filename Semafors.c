#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

// Целевые семафоры
sem_t semaphore1;
sem_t semaphore2;

// Целевая переменная
static int counter = 0;

// Функции потоков
void *waiter(void *args);
void *signaler1(void *args);
void *signaler2(void *args);

// Пример работы с семафорами, позволяющими
// посылать сигналы между потоками
void main(){
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    // Инициализация семафоров
    sem_init(&semaphore1, 0, 0);
    sem_init(&semaphore2, 0, 0);

    // Создание потоков
    pthread_create(&thread1, NULL, waiter, NULL);
    pthread_create(&thread2, NULL, signaler1, NULL);
    pthread_create(&thread3, NULL, signaler2, NULL);

    // Ожидание завершения работы потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Уничтожение семафоров
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    printf("\n");
}

void *waiter(void *args) {
    sleep(3);
    // Ожидание изменения состояния семафора 2
    sem_wait(&semaphore2);
    printf("waiter work!");
}

void *signaler1(void *args) {
    sleep(1);
    // Изменение состояния семафора 1
    sem_post(&semaphore1);
    printf("signaler1 work!");
}

void *signaler2(void *args) {
    sleep(2);
    // Ожидание изменения состояния семафора 1
    sem_wait(&semaphore1);
    // Изменение состояния семафора 2
    sem_post(&semaphore2);
    printf("signaler2 work!");
}
