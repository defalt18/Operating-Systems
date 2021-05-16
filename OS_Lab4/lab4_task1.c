#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t lock_first,lock_second;

void* first(void* data) 
{ 
	printf("First\n"); 
	sem_post(&lock_first);
}
void* second(void* data) 
{ 
	sem_wait(&lock_first);
	printf("Second\n"); 
	sem_post(&lock_first);
	sem_post(&lock_second);
}
void* third(void* data) 
{ 
	sem_wait(&lock_second);
	printf("Third\n"); 
	sem_post(&lock_second);
}

int main () 
{
	sem_init(&lock_first, 1, 0);
	sem_init(&lock_second, 1, 0);
	pthread_t t1, t2, t3;

	sem_wait(&lock_first);
	pthread_create(&t1, NULL, first, NULL);
	pthread_create(&t2, NULL, second, NULL);
	pthread_create(&t3, NULL, third, NULL);

	/* wait for all threads */
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
}
