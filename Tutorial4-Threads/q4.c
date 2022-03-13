#include <stdio.h>
#include <pthread.h>
#define array_size 10
#define no_threads 10

int a[array_size];
int global_index = 0;
int sum = 0;
pthread_mutex_t mutex1;

void *class_total(void *ignored){
    int local_index, partial_sum = 0;
    
    pthread_mutex_lock(&mutex1);
    
    local_index = global_index;
    global_index++;
    
    pthread_mutex_unlock(&mutex1);

    if (local_index < array_size)
        partial_sum += *(a + local_index);
    
    pthread_mutex_unlock(&mutex1);
    
    return 0;
}

int main(){
    int i;

    pthread_t thread_x[10];
    pthread_mutex_init(&mutex1, NULL);

    printf("Enter the grades of ten students\n");

    for(i=0; i<array_size; i++)
        scanf("%d", &a[i]);

    for(i=0; i<no_threads; i++)
        pthread_create(&thread_x[i], NULL, class_total, NULL);

    for(i=0; i<no_threads; i++)
        pthread_join(thread_x[i], NULL);

    printf("The sum of grades is %d\n", sum);
}