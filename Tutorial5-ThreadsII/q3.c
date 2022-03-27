#define _XOPEN_SOURCE 700 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 

int calcFact(int x);
// void *factorial(void *arg);

// global variables
sem_t semaphore;
int moving_sum[5] = {0,0,0,0,0};

// factorial function - recursion 
int calcFact(int x) {
    if (x==1){
        return x;
    } 
	return x * calcFact(x-1);
}

void *factorial(void *arg){
    int *arr = (int *)arg;          // convert pointer arg to int array
	int i = arr[0];                 // retrieved passed arg and saved to i and input
    int input = arr[1]; 

	int fact = calcFact(input);    // call function to calculate Factorial
	
	sem_wait(&semaphore);  // lock semaphore
	
	if (i > 0 && moving_sum[i-1] > 0)
		moving_sum[i] = fact + moving_sum[i-1];
	else
		moving_sum[i] = fact;

	sem_post(&semaphore); // unlock semaphore
	pthread_exit(0);
}

int main(void) { 
    // declare variables
    pthread_t threads[5];  
    int userInput;
    int arr[2] = {0,0};

    sem_init(&semaphore, 0, 1);     // initializze semaphore

    printf("Please enter the following:\n");
    for (int i=0; i<5; i++){
        printf("  Number %d: ", i+1);   // prompt user
        scanf("%d", &userInput);     // scan userInput

        // fill array with inddex and userinput
        arr[0] = i;
        arr[1] = userInput;

        // create thread
        pthread_create(&threads[i], NULL, &factorial, &arr);
    }

    // join threads for factorial
    for (int i=0; i<5; i++){
        pthread_join(threads[i], NULL);
    }

    // free resources
    sem_destroy(&semaphore);

    printf("***************\n");
    
    // print array
	for (int i=0; i<5; i++)
		printf("%d ", moving_sum[i]);
	printf("\n");
} 