#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argv, char** argc) {
    int luis;
    int luis2;
    luis = fork();
    luis2 = fork();
    


    if (luis == 0){
        
        printf("I am child with pid %d: adding the array 2,3,5 and sending partial sum 10 ", getpid()); 
        printf("\n"); 
    }
    
    else if (luis2 == 0){
        
        printf("I am child with pid %d: adding the array 7,1,3 and sending partial sum 11 ", getpid());
        printf("\n");
    }

    else {
       
         printf("I am parent with pid %d sending the array 2,3,5,7,1,3", getpid());
         printf("\n");

        printf("I am parent of pid %i, and pid: %i. I have pid: %d and got partial results 10,11 and final result is 21. ", luis, luis2, getpid());
        printf("\n");

    }

return 0;
}