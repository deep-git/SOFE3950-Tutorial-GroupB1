/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
char *category;
int value;

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];

    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    system("clear");
    printf("--------------------Welcome to JEOPORDY--------------------\n");

    // initialize each of the players in the array
    for(int i=0;  i<NUM_PLAYERS; i++){
        printf("Please enter PLAYER %d name: ", i+1);
        scanf("%s", (char *) &players[i].name);
        players[i].score = 0;
    }

    printf("-----------------------------------------------------------\n");

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {

        // Call functions from the questions and players source files
        display_categories();

        printf("\nCategory: "); 
            scanf("%c", &category);
        printf("Value: "); 
            scanf("%d", &value);

        display_question(category, value);
        

        // Execute the game until all questions are answered

        // Display the final results and exit
        printf("-----------------------------------------------------------\n");
        show_results(players, NUM_PLAYERS);
    }
    return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens) {
  const char *endPoint = " ";

    *tokens = strtok(input, endPoint);
    if (strcmp(*tokens, "who") != 0 || strcmp(*tokens, "what") != 0) {
      return;
    }

    *tokens = strtok(NULL, endPoint);
    if (strcmp(*tokens, "is") != 0) {
      return;
    }

}

void show_results(player *players, int num_players) {
    int max = players[0].score;
    int win = 0;

    for (int i=0; i<num_players; i++){

      if (max < players[i].score) {
        max = players[i].score;
        win = i;
      }

        printf("Name: %s Score: %d\n", players[i].name, players[i].score);
    }

    printf("The winner of the game with a score of %d is %s!", max, players[win].name);
}
