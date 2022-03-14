#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Thread function for calculating the bellcurved grade
void *bellcurve_grad(void *argp){
    sleep(1);
    // Sets grades variable equal to the argument passed through
    float *grades = (float *)argp;
    // Calculates the bellcurved grade
    float bellcurve  = *grades * 1.5;
    // Prints the bellcurved grade
    printf("%f\n", bellcurve);
}

int main(){
  // Declare grade array variable
    float grades[5];

    // Loop to enter and store the 5 students' grades
    for(int i=0; i<5; i++){
        printf("Enter grade of student %d: ", i+1);
        scanf("%f", &grades[i]);
    }

    // Initializes the threads
    pthread_t thread1, thread2, thread3, thread4, thread5;

    // Creates the threads
    pthread_create(&thread1, NULL, bellcurve_grad, (void *)&grades[0]);
    pthread_create(&thread2, NULL, bellcurve_grad, (void *)&grades[1]);
    pthread_create(&thread3, NULL, bellcurve_grad, (void *)&grades[2]);
    pthread_create(&thread4, NULL, bellcurve_grad, (void *)&grades[3]);
    pthread_create(&thread5, NULL, bellcurve_grad, (void *)&grades[4]);

    // Exits the thread
    pthread_exit(NULL);
}
