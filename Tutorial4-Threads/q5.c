#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Defined variables
#define _XOPEN_SOURCE 600
#define COUNT 10
#define INFILE "grades.txt"
#define OUTFILE "bellcurve.txt"

// Declares the global mutex and barrier variables
pthread_mutex_t mutex;
pthread_barrier_t barrier;

// Global variables declared and initialized
int grades[COUNT];
int total_grade = 0;
float total_bellcurve = 0;

// Thread function for reading in the grades from the grades.txt
void *read_grades() {

	// Mutex locks the critical section of the code to prevent thread synchronization
	pthread_mutex_lock(&mutex);

	// Critical section
	// Initializes and opens file
	FILE *fp = fopen(INFILE, "r");
	int i;

	// Reads grades in from file and stores them within the grades array
	for (i=0; i<COUNT; i++)
		fscanf(fp, "%d", &grades[i]);

    // Closes the file
    fclose(fp);

  // Unlock mutex after critical section is done
	pthread_mutex_unlock(&mutex);
	pthread_barrier_wait(&barrier);
	return NULL;
}

// Thread function to bellcurve the grades and append them to the bellcurve.txt
void *save_bellcurve(void *arg) {

	// Creates a barrier wait for all of the threads to finish
	pthread_barrier_wait(&barrier);

	// Mutex locks the critical section of the code to prevent thread synchronization
	pthread_mutex_lock(&mutex);

	// Critical section
	// Sets the variable i equal to the value of the argument being passed through
	int i = *((int*)arg);

	// Increments the total grade by the next value of the grade in the array
	total_grade += grades[i];

	// Calculates the total bellcurve of the grades
	total_bellcurve += (float)grades[i]*1.5;

	// Initializes and opens the file
	FILE *fp = fopen(OUTFILE, "a");

	// Appends the bellcurved grades to the file
	fprintf(fp, "%0.02f\n", (float)grades[i]*1.5);

	// Unlock mutex after critical section is done
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

int main() {

	// Initializes the threads
	pthread_t r_thread;
	pthread_t w_threads[COUNT];

	// Initializes the mutex and barrier
	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, COUNT+1);

	// Creates the thread for reading in the grades from file
	pthread_create(&r_thread, NULL, &read_grades, NULL);

	int i;

	// Creates the threads for the bellcurve function to write to the file
	for (i=0; i<COUNT; i++)
		pthread_create(&w_threads[i], NULL, &save_bellcurve, (void *)(&i));

	// Joins the reading thread
	pthread_join(r_thread, NULL);

	// Joins the bellcurve writing threads
	for (i=0; i<COUNT; i++)
		pthread_join(w_threads[i], NULL);

	// Destroy the barrier and mutex
	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);

	// Print the total grade and class average before and after the grades are bellcurved
    printf("*****BEFORE-(Actual)*****\n");
	printf("Total: %d \nAverage: %0.02f\n", total_grade, (float)(total_grade/COUNT));
	printf("\n");
    printf("*****AFTER-(Bellcurved)*****\n");
	printf("Total: %0.02f \nAverage: %0.02f\n", total_bellcurve, total_bellcurve/COUNT);

	return 0;
}
