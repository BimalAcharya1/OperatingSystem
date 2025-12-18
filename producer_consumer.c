#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define BufferSize 5

sem_t empty;
sem_t full;
int buffer[BufferSize];
pthread_mutex_t mutex;
int in=0, out=0;

void *producer(void *pnum)
{
    int item, i;
    while(1){
        item = rand()%100; // Produce an item randomly
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pnum), buffer[in], in);
        in = (in+1)%BufferSize;
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cnum)
{
    int item;
    int i;
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cnum),item, out);
        out = (out+1)%BufferSize;
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}


int main()
{
    pthread_t pro[3], con[3];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[3] = {1,2,3};
    int i;

    for(i=0; i<3; i++){
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(i=0; i<3; i++){
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(i=0; i<3; i++){
        pthread_join(pro[i], NULL);
    }
    for(i=0; i<3; i++){
        pthread_join(con[i], NULL);
    }

    //pthread_mutex_destroy(&mutex);
    //sem_destroy(&empty);
    //sem_destroy(&full);
    return 0;
}

