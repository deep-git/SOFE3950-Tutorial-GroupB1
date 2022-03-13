#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void *hello_world();
void *goodbye();

int main(void){
    srand(time(NULL));

    pthread_t tid_1, tid_2;
    pthread_create(&tid_1, NULL, (void*)&hello_world, NULL);
    pthread_create(&tid_2, NULL, (void*)&goodbye, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    
    exit(0);
}

void *hello_world(){
    int randTime = rand() % 5;
    sleep(randTime);
    printf("Hello world\n");
    return NULL;
}

void *goodbye(){
    int randTime = rand() % 5;
    sleep(randTime);
    printf("Goodbye\n");
    return NULL;
}