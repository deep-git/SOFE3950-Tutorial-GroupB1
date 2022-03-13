#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT 5

struct student {
	char name[20];
	int student_id;
	int grade;
};

void *bellcurve_grad(void *argp){
    sleep(1);
    struct student *s = argp;
    float bellcurve  = s->grade * 1.5;
    printf("Name: %s ID: %d Curved Grade: %f\n", s->name, s->student_id, bellcurve);
}

int main() {
	struct student students[COUNT];
	pthread_t threads[COUNT];

	int i;
	for (i=0; i<COUNT; i++) {
        printf("Enter Information of Student %d:\n", i+1);
		printf("Name: ");
		scanf("%s", students[i].name);
		
		printf("ID: ");
		scanf("%d", &students[i].student_id);

		printf("Grade: ");
		scanf("%d", &students[i].grade);
	}
    
    printf("\n");

	for (i=0; i<COUNT; i++) 
		pthread_create(&threads[i], NULL, &bellcurve_grad, &students[i]); 

	for (i=0; i<COUNT; i++) 
		pthread_join(threads[i], NULL);

	return 0;
}