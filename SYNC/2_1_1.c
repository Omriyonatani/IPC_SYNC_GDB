// Deadlock

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
	// no matter the other neighbors
	if (state[phnum] == HUNGRY) { 
		// state that eating 
		state[phnum] = EATING; 

		usleep(2000000);
		// lock the right, left.
		// take right fork.
		printf("Philosopher %d takes (right) fork %d\n", phnum + 1, RIGHT+1); 
		sem_wait(&S[RIGHT]);
		// try to take the left and get into the deadlock.
		printf("philosopher %d trying to take (left) fork %d\n", phnum+1,LEFT);
		sem_wait(&S[LEFT]);
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
}

// put down chopsticks 
void put_fork(int phnum) 
{
	// state that thinking 
	state[phnum] = THINKING; 

	printf("Philosopher %d putting fork %d down\n", phnum + 1, RIGHT); 
	printf("Philosopher %d is thinking\n", phnum + 1); 

	// unlock right,left.
	sem_post(&S[RIGHT]); 
	sem_post(&S[LEFT]); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		usleep(1000000); 

		take_fork(*i); 

		usleep(1000000); 

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
		pthread_create(&thread_id[i], NULL, philospher, &phil[i]); 
		printf("Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 
		pthread_join(thread_id[i], NULL); 
} 