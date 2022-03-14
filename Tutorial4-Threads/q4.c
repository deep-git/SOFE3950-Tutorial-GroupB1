#include <stdio.h>
#include <pthread.h>

// Defined variables
#define array_size 10
#define no_threads 10

// Declares and initializes global variables
int a[array_size];
int global_index = 0;
int sum = 0;
pthread_mutex_t mutex1;

// Thread function for the class total
void *class_total(void *ignored){
    int local_index, partial_sum = 0;

    // Mutex lock the critical section to prevent thread synchronization
    pthread_mutex_lock(&mutex1);

    // Critical section
    // Sets local index equal to global index and increments global index
    local_index = global_index;
    global_index++;

    // Unlock mutex
    pthread_mutex_unlock(&mutex1);

    // Calculates the sum
    if (local_index < array_size)
        partial_sum += *(a + local_index);

    // Unlock mutex
    pthread_mutex_unlock(&mutex1);

    return 0;
}

int main(){
    int i;

    // Initializes the thread and mutex
    pthread_t thread_x[10];
    pthread_mutex_init(&mutex1, NULL);

    // Prompt to enter student grades
    printf("Enter the grades of ten students\n");

    // Stores the student grades within an array
    for(i=0; i<array_size; i++)
        scanf("%d", &a[i]);

    // Creates the threads
    for(i=0; i<no_threads; i++)
        pthread_create(&thread_x[i], NULL, class_total, NULL);

    // Joins the threads
    for(i=0; i<no_threads; i++)
        pthread_join(thread_x[i], NULL);

    // Prints the sum of the grades
    printf("The sum of grades is %d\n", sum);
}
