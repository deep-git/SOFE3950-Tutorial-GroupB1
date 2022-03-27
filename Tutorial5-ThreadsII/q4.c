#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

// Define numbers
#define NUMBERS 10

// Declare semaphore
sem_t semaphore;
// Declare and initialize global buffer array
int buffer[5] = {0, 0, 0, 0, 0};

// Producer thread function
void *producer(void *argp) {

  // Convert pointer argp to int array
  int *input = (int *)argp;

  // Define random time
  srand(time(NULL));

  // Loop to go through the numbers
  for (int i = 0; i < NUMBERS; i++) {

    // Loop to go through the buffer
    for (int j = 0; j < 5; j++) {

      // If the buffer at that element is 0, then add input number into buffer
      if (buffer[j] == 0) {

        // Lock semaphore
        sem_wait(&semaphore);

        // Critical section
        // Generate and store random numbers from 1-5 in rand_delay variable
        int rand_delay = rand() % 5 + 1;

        // Sleep for rand_delay amount of time
        sleep(rand_delay);

        // Add the input number to that buffer place
        buffer[j] = input[i];

        // Print the added number
        printf("Produced %d\n", buffer[j]);

        // Unlock semaphore
        sem_post(&semaphore);
        break;
      }

      // If at the end of buffer, set index back to the start of the buffer
      if (j == 4) {
        j = 0;
      }
    }
  }

  // Exit thread
  pthread_exit(0);

}

// Consumer thread function
void *consumer() {
  srand(time(NULL));

  for (int i = 0; i < NUMBERS; i++) {

    for (int j = 0; j < 5; j++) {

      // If buffer at that element is not 0, then set that element to 0
      if (buffer[j] != 0) {
        sem_wait(&semaphore);

        int rand_delay = rand() % 5 + 1;
        sleep(rand_delay);

        // Print the consumed number at that element
        printf("> Consumed %d\n", buffer[j]);

        // Set that element to 0
        buffer[j] = 0;

        sem_post(&semaphore);
        break;
      }

      if (j == 4) {
        j = 0;
      }
    }
  }

  printf("\n");

  pthread_exit(0);

}

int main(void) {

  // Declare and initialize num_input array and threads
  int num_input[NUMBERS];
  pthread_t tid_consumer, tid_producer;

  // Initialize semaphore
  sem_init(&semaphore, 0, 1);

  // Loops through prompting user input of numbers
  for (int i = 0; i < NUMBERS; i++) {
    printf("Please enter number %d: ", i+1);
    // Stores the user entered numbers in the array
    scanf("%d", &num_input[i]);
  }

  printf("\n");

  // Create threads
  pthread_create(&tid_producer, NULL, &producer, &num_input);
  pthread_create(&tid_consumer, NULL, &consumer, NULL);

  // Join threads
  pthread_join(tid_producer, NULL);
  pthread_join(tid_consumer, NULL);

  // Destroy semaphore
  sem_destroy(&semaphore);

  printf("*******************************\n");
  // Print the contents of the buffer
  for (int i = 0; i < 5; i++) {
    printf("Buffer content %d: %d\n", i+1, buffer[i]);
  }
}
