#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 5

sem_t sem;
pthread_mutex_t lock;
int counter = 0;

void *worker(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&sem);
    printf("Thread %d entered\n", id);

    pthread_mutex_lock(&lock);
    counter++;
    printf("Thread %d updated counter = %d\n", id, counter);
    pthread_mutex_unlock(&lock);

    sleep(1);

    printf("Thread %d leaving\n", id);
    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t t[THREADS];
    int id[THREADS];
    int i;

    sem_init(&sem, 0, 3);
    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < THREADS; i++)
    {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, worker, &id[i]);
    }

    for (i = 0; i < THREADS; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("Final counter value = %d\n", counter);

    sem_destroy(&sem);
    pthread_mutex_destroy(&lock);

    return 0;
}
