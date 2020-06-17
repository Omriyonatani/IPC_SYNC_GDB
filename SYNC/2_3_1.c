// Livelock

#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>

#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 

int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 

sem_t mutex; 
sem_t S[N]; 

void test(int phnum) 
{ 
	if (state[phnum] == HUNGRY) { 
		// state that eating 
		state[phnum] = EATING; 

		sleep(2); 
		// every one take right fork.
		printf("Philosopher %d takes fork %d \n", phnum + 1, phnum + 1); 
		// try to take the second, its not possible- try again. and again.. Loop of tries.
		printf("Philosopher %d is waiting to the second fork %d \n", phnum + 1, LEFT + 1); 

		// unlock if someone hungry - eat
		sem_post(&S[phnum]); 
	} 
} 

// take up chopsticks 
void take_fork(int phnum) 
{ 
	// state that hungry 
	state[phnum] = HUNGRY; 

	printf("Philosopher %d is Hungry\n", phnum + 1); 

	// eat if neighbours are not eating 
	test(phnum); 
	// if unable to eat wait to be signalled 
	sem_wait(&S[phnum]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int phnum) 
{ 
	// state that thinking 
	state[phnum] = THINKING; 

	printf("Philosopher %d putting fork %d down\n", phnum + 1, phnum + 1); 
	printf("Philosopher %d is thinking\n", phnum + 1); 
	// check the right only
	test(RIGHT); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		usleep(1000000); 

		take_fork(*i); 

		usleep(000000); 

		put_fork(*i); 
	} 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 

	// initialize the mutexes 
	sem_init(&mutex, 0, 1); 

	for (i = 0; i < N; i++) 

		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 

		// create philosopher processes 
		pthread_create(&thread_id[i], NULL, 
					philospher, &phil[i]); 

		printf("Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 

		pthread_join(thread_id[i], NULL); 
} 