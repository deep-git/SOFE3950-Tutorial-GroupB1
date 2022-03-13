#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define _XOPEN_SOURCE 600

float grades[10];
float total_grade;
float total_bellcurve;
pthread_barrier_t *barrier;

void *save_bellcurve(float *grades) {
    sleep(1);

    total_grade += *grades;
    float total_bellcurve = total_grade * 1.5;

    FILE *file;

    file = fopen("bellcurve.txt", "a");
    fprintf(file, "%f ", total_bellcurve);
    fclose(file);
}

void *read_grades(void *arpg) {
    FILE *file;

    file = fopen("grades.txt", "r");

    for (int i = 0; i < 10; i++) {
        fscanf(file, "%f", &grades[i]);
    }
}

int main() {
    pthread_t thread_read, thread[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&thread_read, NULL, read_grades, (void *)&grades[i]);
    }

    sleep(1);
    pthread_barrier_wait(&barrier);

    for (int i = 0; i < 10; i++) {
        pthread_create(&thread[i+1], NULL, save_bellcurve, (void *)&grades[i]);
    }

    void * t_store[10];

    printf("The total grade before the bellcurve is: %f", total_grade);
    printf("The class average before the bellcurve is: %f", total_grade / 10);

    for (int i = 1; i <= 10; i++) {
        pthread_join(thread[i], t_store[i]);
    }

    pthread_exit(NULL);

    printf("\n");
    printf("The total grade after the bellcurve is: %f", total_grade);
    printf("The class average after the bellcurve is: %f", total_grade / 10);

}
