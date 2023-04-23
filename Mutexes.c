#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Целевая переменная
static int counter = 0;

// Функция, вычитающая из переменной единицу
void *minus(void *);
// Функция, прибавляющая к переменной единицу
void *plus(void *);

// Структура для передачи мьютекса в тело функции через аргумент
typedef struct use_mutex_tag{
    pthread_mutex_t mutex;
} use_mutex_t;

#define NUM_OF_THREADS 100

// Пример работы с мьютексами, позволяющими залочить
// выполнение определенного участка кода для
// использования одним единственным потоком
int main(void) {
    pthread_t threads[NUM_OF_THREADS];
    size_t i;
    use_mutex_t param;  // мьютекс
 
    printf("counter = %d\n", counter);
    // Инициализация мьютекса
    pthread_mutex_init(&(param.mutex), NULL);
    // Создание потоков
    for (i = 0; i < NUM_OF_THREADS/2; i++) {
        pthread_create(&threads[i], NULL, minus, &param);
    }
    for (; i < NUM_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, plus, &param);
    }
    // Ожидание завершения потоков
    for (i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Разрушение мьютекса
    pthread_mutex_destroy(&(param.mutex));
    printf("counter = %d\n", counter);
    return 0;
}

// Функция, вычитающая из переменной единицу
void* minus(void *args) {
    int local;
    use_mutex_t *arg = (use_mutex_t*) args;
    // Захват участка кода
    pthread_mutex_lock(&(arg->mutex));
    local = counter;
    printf("min %d\n", counter);
    local = local - 1;
    counter = local;
    // Разблокирование участка кода
    pthread_mutex_unlock(&(arg->mutex));
    return NULL;
}

// Функция, прибавляющая к переменной единицу
void* plus(void *args) {
    int local;
    use_mutex_t *arg = (use_mutex_t*) args;
    // Захват участка кода
    pthread_mutex_lock(&(arg->mutex));
    local = counter;
    printf("pls %d\n", counter);
    local = local + 1;
    counter = local;
    // Разблокирование участка кода
    pthread_mutex_unlock(&(arg->mutex));
    return NULL;
}
