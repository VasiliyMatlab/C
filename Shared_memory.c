#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

// Пример работы с разделяемой памятью
// На вход поступают ключи двух регионов памяти
// Здесь для создания третьего региона используем ключ 54321,
// хотя в обычных условиях нужно создавать файл и получить
// его ключ с помощью ftok(3)
// В данной программе не обрабатываются ошибки и конфликтные ситуации!
int main(int argc, char *argv[]) {
	// Получаем 3 дескриптора
	int f1 = shmget((key_t) atoi(argv[1]), 1000, IPC_CREAT | 0600);
	int f2 = shmget((key_t) atoi(argv[2]), 1000, IPC_CREAT | 0600);
	int f3 = shmget((key_t) 54321, 1000, IPC_CREAT | 0666);
	// Подстыковываем сегменты разделяемой памяти к адресному
	// пространству текущего процесса
	// Первые два указателя умеют только читать, последний - еще и писать
	int *shared_memory1 = (int *) shmat(f1, NULL, SHM_RDONLY);
	int *shared_memory2 = (int *) shmat(f2, NULL, SHM_RDONLY);
	int *shared_memory3 = (int *) shmat(f3, NULL, 0);
	
	// Суммируем первые 100 чисел и записываем в новую область
	int i = 0;
	for (; i < 100; i++)
		shared_memory3[i] = shared_memory1[i] + shared_memory2[i];
	printf("%d\n", 54321);

	// Отсоединяем сегменты разделяемой памяти
	// от адресного пространства текущего процесса
	shmdt(shared_memory1);
	shmdt(shared_memory2);
	shmdt(shared_memory3);
	return 0;
}