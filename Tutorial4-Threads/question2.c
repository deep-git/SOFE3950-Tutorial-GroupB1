#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define _XOPEN_SOURCE 600

void *bellcurve_grad(void *argp) {
    sleep(1);
    float *grades = (float *)argp;
    float bellcurve = *grades * 1.5;
    printf("%f\n", bellcurve);
}

int main() {
    float grades[5];

    for (int i = 0; i < 5; i++) {
        printf("Enter grade of student %d: ", i + 1);
        scanf("%f", &grades[i]);
    }

    pthread_t thread1, thread2, thread3, thread4, thread5;

    pthread_create(&thread1, NULL, bellcurve_grad, (void *)&grades[0]);
    pthread_create(&thread2, NULL, bellcurve_grad, (void *)&grades[1]);
    pthread_create(&thread3, NULL, bellcurve_grad, (void *)&grades[2]);
    pthread_create(&thread4, NULL, bellcurve_grad, (void *)&grades[3]);
    pthread_create(&thread5, NULL, bellcurve_grad, (void *)&grades[4]);

    void * t_1;
    void * t_2;
    void * t_3;
    void * t_4;
    void * t_5;

    pthread_join(thread1, t_1);
    pthread_join(thread2, t_2);
    pthread_join(thread3, t_3);
    pthread_join(thread4, t_4);
    pthread_join(thread5, t_5);

    pthread_exit(NULL);

}
