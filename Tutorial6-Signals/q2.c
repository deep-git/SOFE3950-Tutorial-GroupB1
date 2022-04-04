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

// Pop function to remove process from the linked list
struct proc* pop(struct queue** head) {
  struct proc* process = NULL;
  struct queue* create_head = NULL;

  // If the head element does not exist, return the process
  if (*head == NULL) {
    return process;
  }

  create_head = (*head)->next;     // Set the head equal to the next element
  process = &(*head)->process;     // Set the process equal to the next process

  free(*head);     // Free the current head element in the linked list
  *head = create_head;     // Set the head equal to the new head

  return process;     // Return the process instance
}

// Pop counter function to determine which element needs to be popped depending on the value entered
struct proc* pop_counter(struct queue** head, int counter) {
  struct queue* current = *head;
  struct proc* process = NULL;

  // If counter equals 0 then return the value of the current head popped
  if (counter == 0) {
    return pop(head);
  }

  // Loop for counter number of times
  for (int i = 0; i < counter; i++) {
    // If the linked list ends after two more elements
    if (current->next->next == NULL) {
      process = &current->next->process;     // Sets the process equal to the next process
      current->next = NULL;     // Sets the next value equal to NULL

      return process;     // Returns the process instance
    }
    current = current->next;     // Sets the current value equal to the next value
  }
  current->next = current->next->next;     // Sets the next value equal to the value after the next value
  process = &current->process;     // Sets the process equal to the next process

  return process;     // Returns the process instance
}

// Delete name function to delete the process with the entered name
struct proc* delete_name(struct queue** head, char *name) {
  struct proc* process = NULL;
  struct queue* current = *head;
  int counter = 0;

  // Loops while the current value is not equal to NULL
  while (current != NULL) {
    process = &current->process;     // Sets the process equal to the next process
    // If the name entered is equal to the process name
    if (strcmp(process->name, name) == 0) {
      return pop_counter(head, counter);     // Returns the process element to be popped
    }
    current = current->next;     // Sets the current equal to the next value
    counter++;     // Increments the counter
  }
  return process;     // Returns the process instance
}

// Delete pid function to delete the process with the entered pid
struct proc* delete_pid(struct queue** head, int pid) {
  struct proc* process = NULL;
  struct queue* current = *head;
  int counter = 0;

  while (current != NULL) {
    process = &current->process;
    // If the process id is equal to the process id entered
    if (process->pid == pid) {
      return pop_counter(head, counter);     // Returns the process element to be popped
    }
    current = current->next;
    counter++;
  }
  return process;     // Returns the process instance
}

void print_proc(struct proc *display_process) {
  // Sets the structure process equal to the parameter value type
  struct proc* process = display_process;

  // Prints the contents of the linked list
  printf("Name: %s\n", process->name);
  printf("Priority: %d\n", process->priority);
  printf("PID: %d\n", process->pid);
  printf("Runtime: %d\n", process->runtime);
  printf("\n");
}

int main(void) {
  struct queue *head = NULL;     // Declare queue structure starting head value NULL since linked list is empty
  struct proc *create_process;     // Declare create_process variable of type proc structure
  char *token;     // Declare token variable
  char read_process_info[256];     // Declare variable to hold each line info from file

  head = malloc(sizeof(struct queue));
  head->next = NULL;     // Sets the next head value of the linked list to NULL
  struct queue* current = head;     // Declare queue structure current value equal to the head

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

  // Call functions to delete name and pid and then print the processes
  print_proc(delete_name(&head, "emacs"));
  print_proc(delete_pid(&head, 12235));
  
  // Loop through the linked list until reaching the end of the list
  while (current->next != NULL) {
    struct proc process = current->process;     // Set process variable equal to the current process
    print_proc(&process);     // Calls the print process method with argument as process
    current = current->next;     // Sets the current variable equal to the next value of the linked list
  }

  // Returns 0
  return 0;
}
