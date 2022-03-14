#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// Calls for initializing the thread functions
void *hello_world();
void *goodbye();

int main(void){
  // Initialize random number
    srand(time(NULL));

    // Initialize threads
    pthread_t tid_1, tid_2;

    // Create threads
    pthread_create(&tid_1, NULL, (void*)&hello_world, NULL);
    pthread_create(&tid_2, NULL, (void*)&goodbye, NULL);

    // Join threads
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    exit(0);
}

// Thread function for printing hello world
void *hello_world(){

  // Generates a random time number between 1 and 5
    int randTime = rand() % 5;
    // Sleeps for that random amount of time
    sleep(randTime);
    // Prints hello world
    printf("Hello world\n");
    return NULL;
}

// Thread function for printing goodbye
void *goodbye(){
  // Generates a random amount of time
    int randTime = rand() % 5;
    // Sleeps for that random amount of time
    sleep(randTime);
    // Prints goodbye
    printf("Goodbye\n");
    return NULL;
}
