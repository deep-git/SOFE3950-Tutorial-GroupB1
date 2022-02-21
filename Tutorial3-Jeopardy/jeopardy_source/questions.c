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

    //------------------------VALUES/QUESTIONS/ANSWERS------------------------


    //------------------------ "Programming" ------------------------
    strcpy(questions[0].question, "A datatype used for data values that are made up of ordered sequences of characters"); 
    strcpy(questions[0].answer, "What is a String"); 
    questions[0].value = 100;

    strcpy(questions[1].question, "A program that processes statements written in a high-level programming language and turns them into machine language or 'code' that a computer's processor uses."); 
    strcpy(questions[1].answer, "What is a Compiler"); 
    questions[1].value = 200;

    strcpy(questions[2].question, "A method for solving complex problems by breaking them down into simpler subproblems"); 
    strcpy(questions[2].answer, "What is dynamic?"); 
    questions[2].value = 300;
    
    strcpy(questions[3].question, "The provision of a single interface to entities of different types."); 
    strcpy(questions[3].answer, "What is encapsulation?"); 
    questions[3].value = 400;

    //------------------------"Algorithms"------------------------
    strcpy(questions[4].question, "A step-by-step instructions used to solve a problem"); 
    strcpy(questions[4].answer, "What is an Algorithm"); 
    questions[4].value = 100;

    strcpy(questions[5].question, "A divide and conquer sorting algorithm."); 
    strcpy(questions[5].answer, "What is Merge Sort");
    questions[5].value = 200;

    strcpy(questions[6].question, "Sequence, Selection and Iteration"); 
    strcpy(questions[5].answer, "What are the three algorithm constructs?");
    questions[6].value = 300;

    strcpy(questions[7].question, "A way of writing an algorithm using structured English"); 
    strcpy(questions[5].answer, "What is pseudocode"); 
    questions[7].value = 400;

    //------------------------"Databases"------------------------
    strcpy(questions[8].question, "Information entered into the computer to be processed that consists of text, numbers, sounds, and images.");    // 100
    strcpy(questions[8].answer, "What is data?");  // 100
    questions[8].value = 100;
  
    strcpy(questions[9].question, "A collection of related information organized for rapid search and retrieval");  // 200
    strcpy(questions[9].answer, "What is database?");  // 200
    questions[9].value = 200;

    strcpy(questions[10].question, "In a datasheet, the table displays its data in rows and columns that forms queries"); // 300  
    strcpy(questions[10].answer, "What is datasheet?"); // 300  
    questions[10].value = 300;

    
    strcpy(questions[11].question, "Allows you to design and format an Access object (used for forms, query, tables and reports)."); // 400
    strcpy(questions[11].answer, "What is design view?"); // 400
    questions[11].value = 400;

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
