/**
 * Zach Sotak
 * 3/20/2018
 *
 * To compile
 * Compiles in Codeblocks, not in Putty
 *
 */

#include <windows.h>
#include <stdio.h>
#define SIZE 45

DWORD fibArray[SIZE]; /* data is shared by thread(s) */

/* the thread runs in this seperate function */
DWORD WINAPI fibCalc(LPVOID Param){
    DWORD input = *(DWORD*)Param;

    /* Set temp variables to 0 and 1 respectively to start the fibonacci sequence */
    DWORD temp0 = 0, temp1 = 1, temp2;
    fibArray[0] = temp0;
    fibArray[1] = temp1;

    /* After the 2 starting values, each number is the sum of the 2 preceding numbers
     * So we set the sum to temp2 and add it to the array, and move the first 2 variables up.
     */
    for(DWORD i = 2; i < input; i++){
        temp2 = temp0 + temp1;
        temp0 = temp1;
        temp1 = temp2;
        fibArray[i] = temp2;
    }
    return 0;
}

int main(int argc, char *argv[]){
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int input;

    printf("Enter a number between 1 and 45: ");
    scanf("%d", &input);

    while (input <= 0 || input >= 46){
        fprintf(stderr,"The argument (%d) must be between 1 and 45\n",input);
        printf("Enter a number between 1 and 45: ");
        scanf("%d", &input);
    }

    /* Create the thread */
    ThreadHandle = CreateThread(
                       NULL, /* default security stuff */
                       0, /* default stack size */
                       fibCalc, /* thread function */
                       &input, /* parameter to thread function */
                       0, /* default creation flags */
                       &ThreadId); /* returns the thread identifier */

    if (ThreadHandle != NULL){
        /* now wait for the thread to finish */
        WaitForSingleObject(ThreadHandle,INFINITE);

        /* close the thread handle */
        CloseHandle(ThreadHandle);

        printf("The generated fibonacci sequence is:\n");
        for ( int i=0 ; i < input ; i++){
            printf("Fibonacci number fib(%d) = %d\n", i , fibArray[i]);
        }
    }
    return 0;
}
