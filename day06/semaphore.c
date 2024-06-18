#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0); // 초기값 0
	sem_init(&sem_two, 0, 1); // 초기값 1

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one); // 생성했던 semaphore 소멸시킴
	sem_destroy(&sem_two);
	return 0;
}

void * read(void * arg)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		fputs("Input num : ", stdout);

		sem_wait(&sem_two); // 키 획득
		scanf("%d", &num);
		sem_post(&sem_one); // 1을 증가시킴(sem_one에 키 할당)
	}
	return NULL;
}
void * accu(void * arg)
{
	int sum = 0, i;
	for(i = 0; i < 5; i++)
	{
		sem_wait(&sem_one); // 키 획득
		sum += num;
		sem_post(&sem_two); 
	}
	printf("Result : %d \n", sum);
	return NULL;
}
