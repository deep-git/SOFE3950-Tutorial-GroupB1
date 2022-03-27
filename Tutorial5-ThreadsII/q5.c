#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Define files
#define FILE1 "numbers.txt"
#define FILE2 "sum.txt"

// Declare and initialize global variables
sem_t semaphore; // Declare global semaphore
int total_sum = 0;
int fork();
int waitpid();

// Factorial thread function
void *factorial(void *argp) {

	int input = *((int *)argp);     // Converts the pointer argp to the int value
	int calc = 1;

	for (int i = 1; i <= input; i++) {
		calc = calc * i;     // Calculates the factorial of each number
	}

	printf("Calculated factorial %d = %d\n", input, calc); // Prints the calculated factorial for each number entered

	sem_wait(&semaphore);     // Locks semaphore

	// Critical section
	total_sum = total_sum + calc;     // Calculates the total sum of all the calculated factorials

	sem_post(&semaphore);     // Unlocks semaphore

	pthread_exit(0);     // Exits thread
}

int main(void) {
	// Declare and initialize array, process, and thread variables
	int num_input[5];
	int read_num[5];
	pid_t pid1;
	pthread_t tid_factorial[5];

	sem_init(&semaphore, 0, 1);     // Initialize semaphore

	FILE *file1 = fopen(FILE1, "w");     // Open numbers file to write
	for (int i = 0; i < 5; i++) {
		printf("Enter number %d: ", i+1);
		scanf("%d", &num_input[i]);     // Scan and store user input into array
		fprintf(file1, "%d\n", num_input[i]);     // Write array numbers to file
	}

	fclose(file1);     // Close file

	if ((pid1 = fork()) == 0) {     // Child process

		file1 = fopen(FILE1, "r");     // Open numbers file to read

		for (int i = 0; i < 5; i++) {
			fscanf(file1, "%d\n", &read_num[i]);      // Read numbers from the file into the array
			printf("Thread %d with number = %d\n", i+1, read_num[i]);     // Print the numbers from the array
			pthread_create(&tid_factorial[i], NULL, &factorial, &read_num[i]);     // Create thread and pass number from array as argument
		}

		fclose(file1);     // Close file

		for (int i = 0; i < 5; i++) {
			pthread_join(tid_factorial[i], NULL);     // Join threads
		}

		file1 = fopen(FILE2, "w");     // Open sum file to write
		fprintf(file1, "%d", total_sum);     // Write the total sum to the sum file

		fclose(file1);     // Close file

	} else {     // Master/Parent process

		waitpid(pid1, NULL, 0);     // Wait for child process

		int read_sum;
		file1 = fopen(FILE2, "r");     // Open sum file to read
		fscanf(file1, "%d", &read_sum);     // Read total sum from sum file and store in read_sum variable
		printf("**************************\n");
		printf("Total sum: %d\n", read_sum);     // Print the total sum
	}

	sem_destroy(&semaphore);     // Destroy semaphore
}
