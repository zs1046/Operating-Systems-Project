/**
 * Zach Sotak
 * 3/20/2018
 *
 * To compile
 * g++ pthreadFibo.cpp -lpthread
 *
 * To run
 * ./a.out
 */

#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
#define SIZE 45

long fibArray[SIZE]; /* Fibonacci Array shared by threads */
int input = 0; /* this data is shared by the thread(s) */

void *fibCalc(void *param); /* the thread */

int main()
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    printf("Enter a number between 1 and 45: ");
    scanf("%d", &input);

    while (input <= 0 || input >= 46)
    {
        fprintf(stderr,"The argument (%d) must be between 1 and 45\n",input);
        printf("Enter a number between 1 and 45: ");
        scanf("%d", &input);
    }

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid,&attr,fibCalc,(void *) &input);

    /* now wait for the thread to exit */
    pthread_join(tid,NULL);

    printf("The generated fibonacci sequence is:\n");
    for (int i = 0; i < input; i++)
    {
        printf("Fibonacci number fib(%d) = %d\n", i , fibArray[i]);
    }

    return 0;
}

/**
 * The thread will begin control in this function
 */
void *fibCalc(void *param)
{
    int input = *(int*)(param);

    /* Set temp variables to 0 and 1 respectively to start the fibonacci sequence */
    int temp0 = 0, temp1 = 1, temp2;
    fibArray[0] = temp0;
    fibArray[1] = temp1;

    /* After the 2 starting values, each number is the sum of the 2 preceding numbers
     * So we set the sum to temp2 and add it to the array, and move the first 2 variables up.
     */
    for(int i = 2; i < input; i++)
    {
        temp2 = temp0 + temp1;
        temp0 = temp1;
        temp1 = temp2;
        fibArray[i] = temp2;
    }
    pthread_exit(0);
}
