/**
 * Zach Sotak
 * 3/20/2018
 *
 * To compile
 * gcc -o matrix matrixMultPthreads.c -lpthread
 *
 * To run
 * ./matrix
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3
#define NUM_THREADS M*N


int A [M][K] = {{1, 4}, {2, 5}, {3, 6}}; /* Matrix A*/
int B [K][N] = {{8, 7, 6}, {5, 4, 3}}; /* Matrix B*/
int C [M][N]; /* Matrix C*/

void *matrixMultiplication(void *param);

/* structure for passing data to threads */
struct v{
    int i;  /* row */
    int j;  /* column */
};

int main(){
    int counter = 0;
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    pthread_t workers[NUM_THREADS];

    /* We have to create M x N worker threads */
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            struct v *data = (struct v*)malloc(sizeof(struct v));
            data->i = i;
            data->j = j;
            /*Now create the thread passing its data as a parameter*/

            /* get the default attributes */
            pthread_attr_init(&attr);

            /* create the thread */
            pthread_create(&workers[counter], &attr, matrixMultiplication, data);

            counter++;
        }
        /* now wait for threads to finish */
        pthread_join(workers[i], NULL);
    }

    /* print matrix C */
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/**
 * The thread will begin control in this function
 * Given two matrices, A and B, where matrix A contains
 * M rows and K columns and matrix B contains K
 * rows and N columns, the matrix product of A and B is
 * matrix C, where C contains M rows and N columns.
 */
void *matrixMultiplication(void *param){
    struct v *data = param;
    int sum = 0;

    for(int i = 0; i < K; i++){
        sum += A[data->i][i] * B[i][data->j];
        C[data->i][data->j] = sum;
    }
    pthread_exit(0);
}
