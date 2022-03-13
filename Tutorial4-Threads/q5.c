#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define _XOPEN_SOURCE 600 
#define COUNT 10
#define INFILE "grades.txt"
#define OUTFILE "bellcurve.txt"

pthread_mutex_t mutex;
pthread_barrier_t barrier;

int grades[COUNT];
int total_grade = 0;
float total_bellcurve = 0;

void *read_grades() {
	pthread_mutex_lock(&mutex); 
	
	FILE *fp = fopen(INFILE, "r");
	int i;
	for (i=0; i<COUNT; i++)
		fscanf(fp, "%d", &grades[i]);
	
    fclose(fp);
	
	pthread_mutex_unlock(&mutex); 
	pthread_barrier_wait(&barrier); 
	return NULL;
}

void *save_bellcurve(void *arg) {
	pthread_barrier_wait(&barrier); 
	pthread_mutex_lock(&mutex); 
	
	int i = *((int*)arg); 

	total_grade += grades[i];
	total_bellcurve += (float)grades[i]*1.5;
	
	FILE *fp = fopen(OUTFILE, "a");
	fprintf(fp, "%f\n", (float)grades[i]*1.5);

	pthread_mutex_unlock(&mutex); 
	pthread_exit(0); 
}

int main() {
	pthread_t r_thread;
	pthread_t w_threads[COUNT];
	
	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, COUNT+1);
	pthread_create(&r_thread, NULL, &read_grades, NULL);

	int i;

	for (i=0; i<COUNT; i++)
		pthread_create(&w_threads[i], NULL, &save_bellcurve, (void *)(&i));

	pthread_join(r_thread, NULL);

	for (i=0; i<COUNT; i++)
		pthread_join(w_threads[i], NULL);

	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);
	
    printf("*****BEFORE-(Actual)*****\n");
	printf("Total: %d \nAverage: %f\n", total_grade, (float)(total_grade/COUNT));
    printf("*****AFTER-(Bellcurved)*****\n");
	printf("Total: %f \nAverage: %f\n", total_bellcurve, total_bellcurve/COUNT);
	
	return 0;
}
