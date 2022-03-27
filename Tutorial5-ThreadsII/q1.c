#define _XOPEN_SOURCE 700 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 

#define FILE1 "child1.txt"
#define FILE2 "child2.txt"

int sleep();		// declare functions
int fork();			
int waitpid();

int main(void) { 
    pid_t pid1, pid2;		// declare processID
	char str[20];			// for fgets() function

	if ((pid1 = fork()) == 0) { 				// **** CHILD 1 ****
		sleep(1);								// wait 1 sec

		FILE *file1 = fopen(FILE1, "r");		// open file to be read
		fgets(str, 20, file1);					// read from file
		fclose(file1);							// close file

		printf("%s\n", str);					// print file to console
	} 
	else {
		if ((pid2 = fork()) == 0) { 			// **** CHILD 2 ****
			sleep(1);							

			FILE *file2 = fopen(FILE2, "r");
			fgets(str, 20, file2);
			fclose(file2);

			printf("%s\n", str);
		} 
		else { 									// **** MASTER/PARENT ****
			FILE *file1 = fopen(FILE1, "w");	// open both files to write to
			FILE *file2 = fopen(FILE2, "w");

			fprintf(file1, "child 1");			// write to file
			fprintf(file2, "child 2");

			fclose(file1);						// close both files
			fclose(file2);

			printf("master process\n");			// print to console
			
			waitpid(pid1, NULL, 0);				// wait until child has changed state
			waitpid(pid2, NULL, 0);
		}
	}
} 