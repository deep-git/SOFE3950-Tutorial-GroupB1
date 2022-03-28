#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Define process.txt file
#define FILE1 "processes.txt"

// Create structure for proc with declared variables
struct proc {
  char name[256];
  int priority;
  int pid;
  int runtime;
};

// Create linked list queue with declared structure variables
struct queue {
  struct proc process;     // Declared variable creates an instance of proc structure
  struct queue *next;     // Declared variable creates a pointer to the next linked list structure
};

// Push function to add each process to the linked list
void push(struct queue *head, struct proc create_process) {
  struct queue *current = head;
  struct proc process = create_process;

  // While the next item exists, set the current to the next item
  while (current->next != NULL) {
    current = current->next;
  }

  // Adds a new process
  current->next = malloc(sizeof(struct queue));
  current->next->process = process;
  current->next->next = NULL;
}

int main(void) {
  struct queue *head = NULL;
  struct proc *create_process;
  char *token;     // Declare token variable
  char read_process_info[256];     // Declare variable to hold each line info from file

  head = malloc(sizeof(struct queue));
  head->next = NULL;     // Sets the next head value of the linked list to NULL

  FILE *file1 = fopen(FILE1, "r");     // Opens the processes.txt file in read mode

  // Reads in from file using tokens to separate commas and content
  while (fgets(read_process_info, sizeof(read_process_info), file1) != NULL) {
    create_process = malloc(sizeof(struct proc));

    // First name section (start to first comma)
    token = strtok(read_process_info, ",");
    // strcpy because name variable is a string
    strcpy(create_process->name, token);     // Copies the name token to the name variable of the structure

    // Second priority section (NULL after previous comma to next comma)
    token = strtok(NULL, ",");
    // sscanf because priority variable is an integer
    sscanf(token, "%d", &create_process->priority);     // Copies the next token to the priority variable (int)

    // Third pid section (NULL after previous comma to next comma)
    token = strtok(NULL, ",");
    // sscanf because pid variable is an integer
    sscanf(token, "%d", &create_process->pid);     // Copies the next token to the pid variable (int)

    // Fourth runtime section (NULL after previois comma to end line)
    token = strtok(NULL, "\n");
    // sscanf because runtime variable is an integer
    sscanf(token, "%d", &create_process->runtime);     // Copies the next token to the runtime variable (int)

    // Adds/Pushes the content to the end of the linked list
    push(head, *create_process);
  }

  // Prints the contents of the linked list
  printf("Name: %s\n", create_process->name);
  printf("Priority: %d\n", create_process->priority);
  printf("PID: %d\n", create_process->pid);
  printf("Runtime: %d\n", create_process->runtime);

  return 0;
}
