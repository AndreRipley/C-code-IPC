#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argv, char** argc) {
    // initialize pipes
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int luis;

    int numElements = 6; //num of elements in the array
    luis = fork();  //creating a child

    if (luis == 0) { // If I am the child read the elements of the array that my parent sent me
        
        close(p1[1]); //closing the writing end of pipe1 (p1), I am using p1 for reading so p1[0] is open for reading from my parent
        close(p2[0]); //closing the  reading end of pipe2 (p2), I am using p2 for sending (writing) the sumation to my parent 
        int vals[numElements];
        read(p1[0], &vals, sizeof(vals));

        // compute the sum
        int sum = 0;
        printf("child %d: received ", getpid()); //printing my pid and the array that I just received from my parent
        int i;
        for (i=0;i<numElements;i++){   
            printf("%d, ", vals[i]);
            sum += vals[i];    //Adding the elments of the array
        }
        printf("\n");   
        printf("child %d: sending %d to parent\n", getpid(), sum); 
        // send result to parent
        write(p2[1], &sum, sizeof(sum)); //sending to the parent the sum of the array
        exit(0);     //key line of code.
    } else {
        // parent
        close(p1[0]);  //closing reading, because I will use pipe1 for sending info to my child
        close(p2[1]);  //closing writing, bacuase I will use this pipe2 for receiving the summation from my child 
        // send values to child
        int valsToSend[6] = {2,3,5,7,1,3};
        write(p1[1], &valsToSend, sizeof(valsToSend));
        printf("parent is %d\n", getpid());
        // receive and print the final value
        int recval;
        read(p2[0], &recval, sizeof(recval));
        printf("parent: final sum is %d\n", recval);
        exit(0);
    }
    return 0;
}
