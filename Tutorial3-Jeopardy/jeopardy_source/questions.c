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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
      strcpy(questions[i].category, categories[i % NUM_CATEGORIES]);
      questions[i].answered = false;
    }

    //------------------------VALUES------------------------
    // "Programming" 
    questions[0].value = 100;
    questions[1].value = 200;
    questions[2].value = 300;
    questions[3].value = 400;

    // "Algorithms" 
    questions[4].value = 100;
    questions[5].value = 200;
    questions[6].value = 300;
    questions[7].value = 400;

    // "Databases"
    questions[8].value = 100;
    questions[9].value = 200;
    questions[10].value = 300;
    questions[11].value = 400;

    //------------------------QUESTIONS------------------------
    // "Programming" 
    strcpy(questions[0].question, "what is 1+1"); // 100
    strcpy(questions[1].question, "what is 2+2"); // 200
    strcpy(questions[2].question, "what is 3+3"); // 300
    strcpy(questions[3].question, "what is 4+4"); // 400

    // "Algorithms"
    strcpy(questions[4].question, "what is 5+5"); // 100
    strcpy(questions[5].question, "what is 6+6"); // 200
    strcpy(questions[6].question, "what is 7+7"); // 300
    strcpy(questions[7].question, "what is 8+8"); // 400

    // "Databases"
    strcpy(questions[8].question, "what is 9+9");    // 100
    strcpy(questions[9].question, "what is 10+10");  // 200
    strcpy(questions[10].question, "what is 11+11"); // 300  
    strcpy(questions[11].question, "what is 12+12"); // 400

    //------------------------ANSWERS------------------------
    // "Programming" 
    strcpy(questions[0].answer, "2"); // 100
    strcpy(questions[1].answer, "4"); // 200
    strcpy(questions[2].answer, "6"); // 300
    strcpy(questions[3].answer, "8"); // 400

    // "Algorithms"
    strcpy(questions[4].answer, "10"); // 100
    strcpy(questions[5].answer, "12"); // 200
    strcpy(questions[6].answer, "14"); // 300
    strcpy(questions[7].answer, "16"); // 400

    // "Databases"
    strcpy(questions[8].answer, "18");  // 100
    strcpy(questions[9].answer, "20");  // 200
    strcpy(questions[10].answer, "22"); // 300  
    strcpy(questions[11].answer, "24"); // 400

    
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
      if (questions[i].answered ==  false) {
        printf("%i ", questions[i].value);
      }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for (int i=0; i < NUM_QUESTIONS; i++){
      if (questions[i].value == value && strcmp(questions[i].category, category) == 0){
        printf("%s",questions[i].question);
      } 
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for (int i=0; i < NUM_QUESTIONS; i++){
      if (questions[i].value == value && strcmp(questions[i].category, category) == 0){ 
        if (questions[i].answer == answer){
          return true;
        }
      }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for (int i = 0; i < NUM_QUESTIONS; i++) {

      // Checks to see if the questions value and the category match according to a previous entry, if it does then returns true as the question has already been answered
      if (questions[i].value == value && strcmp(questions[i].category, category) == 0) {
        return true;
      }
    }

    // Returns false if the question has not yet been answered
    return false;
}
