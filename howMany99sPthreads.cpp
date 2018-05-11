/**
 * Zach Sotak
 * 3/20/2018
 *
 * To compile
 * g++ howMany99sPthreads.cpp -lpthread
 *
 * To run
 * ./a.out
 */
#include <omp.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdio>

#define SIZE 100000
#define NUM_THREADS 2

using namespace std;

int myArray [SIZE];
int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *howMany(void *param); /* the thread */

int main(){
    double start_time, end_time;
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    pthread_t workers[NUM_THREADS];
    int thread[NUM_THREADS];

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initialize random number generator
    srand((unsigned)time(NULL));


    // Initialize the array using random numbers
    for (int i = 0; i < SIZE; i++)
        myArray[i] = rand() % 100;

    //Serial Code
    start_time = omp_get_wtime();

     for (int i = 0; i < NUM_THREADS; i++){
        pthread_attr_init(&attr);
        thread[i] = i;

        /* create the thread */
        pthread_create(&workers[i],&attr,howMany,(void *) &thread[i]);

        /* now wait for threads to finish */
        pthread_join(workers[i], NULL);
    }
    end_time = omp_get_wtime();

    printf ("The Pthread code indicates that there are %d 99s in the array.\n\n", counter);
    printf ("The Pthread code used %f seconds to complete the execution.\n\n", end_time - start_time);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    return 0;
}

void *howMany(void *param){
    int begin, end, tid = *(int *)param;

    begin = tid * (SIZE / NUM_THREADS);
    end = begin + (SIZE / NUM_THREADS);

    pthread_mutex_lock(&mutex);
    for (int i = begin; i < end; i++) {
        if (myArray[i] == 99)
            counter++;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}


