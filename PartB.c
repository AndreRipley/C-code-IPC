// Cody Carroll
// OS Concepts
// Programming Assignment 1
// Part B (Extension of Part A)
// Fall 2018

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

// Main function/only function
int main(int argc, const char* argv[]) {
    // Amount of children
    int n = 3;
    // Declaring of a Process ID value
    pid_t pids[n];
    // Declaring pipelines
    // Each pipe is holding a different part of the array
    int cc[2], cc1[2], cc2[2], cc3[2], cc4[2];
    pipe(cc);
    pipe(cc1);
    pipe(cc2);
    pipe(cc3);
    pipe(cc4);
    // Declaring the array
    int array[] = {3,6,2,7,1,5};
    // The sum of the array
    int arraySum = 0;
    // The position in the array
    int posindex = 0;
    int div_index = 0;
    int n_index = 0;
    int child_Sum = 0;
    // Length of the array
    int arraySize = sizeof(array)/sizeof(int);
    // The division of the array
    int divPoint = (arraySize / n);
    int s_Array[n][divPoint];
    int unionArray[n];
    printf("The parent process is running, and has an array size of %d. pid:%d\n", arraySize, getpid());
    printf("The array is in %d pieces\n", n);
    for (int a=0; a < arraySize; a++) {
        if ((a % divPoint) == 0 && (a != 0)) {
            printf("%d | %d\n", a, divPoint);
            n_index++;
            div_index = 0;
        }
        printf("di: %d\n", div_index);
        s_Array[n_index][div_index] = array[a];
        printf("sArray[%d][%d] = %d\n", n_index, div_index, s_Array[n_index][div_index]);
        div_index++;
    }
    write(cc[1], &child_Sum, sizeof(child_Sum));
    write(cc1[1], &s_Array, sizeof(s_Array));
    write(cc2[1], &unionArray, sizeof(unionArray));
    write(cc3[1], &divPoint, sizeof(divPoint));
    for (int i=0; i < n; ++i) {
        if ((pids[i] = fork()) < 0) {
            abort();
        }
        else if (pids[i] == 0) {
            for (int b=0; b < divPoint; b++) {
                printf("%d-%d --> %d\n", i, b, s_Array[i][b]);
                child_Sum += s_Array[i][b];
            }
            printf("%d\n", child_Sum);
            printf("Child Process: pid=%d; Child_Sum=%d\n", getpid(), child_Sum);
            write(cc4[1], &child_Sum, sizeof(child_Sum));
            exit(0);
        }
    }
    while (n > 0) {
        wait(NULL);
        read(cc4[0], &child_Sum, sizeof(child_Sum));
        arraySum += child_Sum;
        --n;
    }
    printf("Final sum of the parent process: Process ID:%d\n", getpid());
    printf("Total sum = %d\n", arraySum);
}