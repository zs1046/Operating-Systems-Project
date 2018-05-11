/**
 * Zach Sotak
 * 3/20/2018
 *
 * To compile
 * g++ howMany99sOMP.cpp -lgomp
 *
 * To run
 * ./a.out
 */
#include <omp.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdio>

using namespace std;

int main()
{
    int count = 0, i;
    int const SIZE = 100000;
    int myArray [SIZE];
    double start_time, end_time;

    //initialize random number generator
    srand((unsigned)time(NULL));

    // Initialize the array using random numbers
    for (i = 0; i < SIZE; i++)
        myArray[i] = rand() % 100;

    //Serial Code
    start_time = omp_get_wtime();
    omp_set_num_threads(2);
    #pragma omp parallel for private(i) shared(myArray, SIZE) reduction(+:count)
    for (i = 0; i < SIZE; i++){
        if (myArray[i] == 99)
            count ++;
    }
    end_time = omp_get_wtime();

    printf ("The OpenMP code indicates that there are %d 99s in the array.\n\n", count);
    printf ("The OpenMP code used %f seconds to complete the execution.\n\n", end_time - start_time);

    return 0;
}

