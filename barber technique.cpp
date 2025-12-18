#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3
#define CUSTOMERS 8

sem_t customerReady;
sem_t barberReady;
pthread_mutex_t mutex;

int waiting = 0;

void *barber(void *arg)
{
    while (1)
    {
        sem_wait(&customerReady); // wait for customer

        pthread_mutex_lock(&mutex);
        waiting--; // one customer goes to barber chair
        printf("Barber: Taking a customer. Waiting customers = %d\n", waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&barberReady); // signal barber is ready

        printf("Barber: Cutting hair...\n");
        sleep(2); // haircut time
        printf("Barber: Finished haircut.\n");
    }
}

void *customer(void *num)
{
    int id = *(int *)num;

    pthread_mutex_lock(&mutex);

    if (waiting < CHAIRS)
    {
        waiting++;
        printf("Customer %d: Sitting in waiting room. Waiting = %d\n", id, waiting);

        pthread_mutex_unlock(&mutex);

        sem_post(&customerReady); // notify barber
        sem_wait(&barberReady);   // wait for barber

        printf("Customer %d: Getting haircut.\n", id);
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        printf("Customer %d: No chair available. Leaving.\n", id);
    }

    return NULL;
}

int main()
{
    pthread_t barberThread, custThread[CUSTOMERS];
    int ids[CUSTOMERS];

    sem_init(&customerReady, 0, 0);
    sem_init(&barberReady, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&barberThread, NULL, barber, NULL);

    for (int i = 0; i < CUSTOMERS; i++)
    {
        ids[i] = i + 1;
        sleep(1); // customers arrive one by one
        pthread_create(&custThread[i], NULL, customer, &ids[i]);
    }

    for (int i = 0; i < CUSTOMERS; i++)
        pthread_join(custThread[i], NULL);

    printf("\nAll customers processed.\n");

    return 0;
}

