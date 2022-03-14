#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Defined variables
#define COUNT 5

// Create structure for student relative information
struct student {
	char name[20];
	int student_id;
	int grade;
};

// Thread function for calculating the bellcurved grade
void *bellcurve_grad(void *argp){
    sleep(1);
		// Sets the value of student structure variable equal to the argument being passed through
    struct student *s = argp;
		// Calculates the bellcurved grade
    float bellcurve  = s->grade * 1.5;
		// Prints the student name, student id, and their corresponding bellcurved grade
    printf("Name: %s ID: %d Curved Grade: %f\n", s->name, s->student_id, bellcurve);
}

int main() {
	// Initializes the structure and thread variables
	struct student students[COUNT];
	pthread_t threads[COUNT];

	int i;

	// Loop for entering and storing student names, id, and their corresponding grades
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

	// Loop to create the threads
	for (i=0; i<COUNT; i++)
		pthread_create(&threads[i], NULL, &bellcurve_grad, &students[i]);

	// Loop to join the threads
	for (i=0; i<COUNT; i++)
		pthread_join(threads[i], NULL);

	return 0;
}
