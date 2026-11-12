#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
sem_t room;

void *philosopher(void *arg)
{
    int i = *(int *)arg;

    printf("Philosopher %d is thinking\n", i);
    sleep(1);

    sem_wait(&room);
    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i + 1) % N]);

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&chopstick[(i + 1) % N]);
    sem_post(&chopstick[i]);
    sem_post(&room);

    printf("Philosopher %d finished eating\n", i);

    return NULL;
}

int main()
{
    pthread_t t[N];
    int id[N];
    int i;

    sem_init(&room, 0, N - 1);

    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (i = 0; i < N; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("All philosophers have eaten. No deadlock occurred.\n");

    return 0;
}
