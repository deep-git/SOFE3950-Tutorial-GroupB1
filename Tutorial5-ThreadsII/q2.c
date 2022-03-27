#define _XOPEN_SOURCE 700 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 

int sleep();		// declare functions
int fork();			
int waitpid();

int main(void) { 
    pid_t pid1;		// declare processID

    if ((pid1 = fork()) == 0) { 				// **** CHILD 1 ****
        sleep(1);								// wait 1 sec
        printf("Child process\n");				// print file to console
	} 
	else {                                      // **** PARENT ****
			printf("Parent process\n");			// print to console
			waitpid(pid1, NULL, 0);		        // wait until child has changed state
    }
}