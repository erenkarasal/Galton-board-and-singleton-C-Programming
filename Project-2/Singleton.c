#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define NO_OF_THREADS 10

// **Eren karasal 39614187098 my code explainations
// **are on next to the codes    

struct Singleton
{
	char *Data; // data parameter
};

struct Singleton *singletonObjectPointer; //instance parameter

int addresses[NO_OF_THREADS];
sem_t sem;

void *runner(void *params); /* the thread */
struct Singleton *getInstance();

int main() //main method
{
	int i;
	sem_init(&sem, 0, 1);
	pthread_t threadIds[NO_OF_THREADS];

	for (i = 0; i < NO_OF_THREADS; i++)
	{
		pthread_create(&threadIds[i], NULL, &runner, (void *)(i));
	}

	/* Wait until all threads are done */
	for (i = 0; i < NO_OF_THREADS; i++)
	{
		pthread_join(threadIds[i], NULL);
	}

	/* Control addresses. All of them should be same */
	int prevAddr = addresses[0];
	for (i = 1; i < NO_OF_THREADS; i++)
	{
		if (addresses[i] != prevAddr)
		{
			printf("Object is created more than once\n");
			return -1;
		}
		prevAddr = addresses[i];
	}
	for (i = 0; i < NO_OF_THREADS; i++)
	{
		printf("Singleton Addresses for each thread %x\n", addresses[i]);
	}
	//	printf("Successful\n");
	return 1;
}

/**
 * The thread will begin control in this function
 */
void *runner(void *params)
{
	int i = (int)params;
	printf("Thread %d\n", i);
	struct Singleton *s = getInstance();
	addresses[i] = s;
	pthread_exit(0);
}

//Fill this method
struct Singleton *getInstance() // instance metodu
{
	static pthread_mutex_t aLock = PTHREAD_MUTEX_INITIALIZER;//Lock for synchronization
	if (singletonObjectPointer == NULL) // if object is null get in this statement
	{
		pthread_mutex_lock(&aLock); //this is for locking the statement
		if (singletonObjectPointer == NULL) // if lock the statement and null get in this statement
		{

			pthread_mutex_unlock(&aLock); // unlock the object 
			singletonObjectPointer = (struct Singleton *)malloc(sizeof(struct Singleton));

			printf("---Address of singletonObjectPointer is %x\n", singletonObjectPointer);
			singletonObjectPointer->Data = "This is object data";

			
		}
		pthread_mutex_unlock(&aLock); // unlock the first statement
	}

	return singletonObjectPointer; // return : object
}
