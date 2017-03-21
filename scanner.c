/***************************************************************
* The main logic of scanning the sample file.
* Saves all the identifiers to the linked list.
* Uses a state machine concept to process the tokens in the file.
* @author Gloire Rubambiza
* @version 03/13/2017
* @filename: scanner.c
* Project developed as part of the System Programming
* class(CIS 361) at Grand Valley State University.
* Copyright (c) 2017 Gloire Rubambiza All Rights Reserved.
* *************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#define MAX 50

/************************************************
* Uses state to know the next character read from
* the local file. Builds a string if an identifier
* is found. The states are as follow:
* 0 is space, 1 is alphanum, 2 is comments, 3 is
* string quotes, 4 is newline/tab, 5 for symbols
**************************************************/
int main(int argc, char ** argv){

  // Initialize all global variables
  int state = 0;
  char ch, temp;
  int tempcount = 0;

  // Initialize the linked-list of identifiers
  List * MyList = initialize();

  // Open the file to be scanned
  FILE * fin = fopen(argv[1], "r");
  if(fin == NULL){
    fprintf(stderr, "File named sample.c not found\n\n");
    exit(1);
  }

  while ( ch = fgetc(fin), ch != EOF){ // Switch state based on new char
    switch (state) {
      case 0:
      if (isalpha(ch)){ // State: space to word
        state = 1;
        int counter = 0;
        char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
        token[counter] = ch; // Add the first character
        counter++; // Increment the counter;
        temp = fgetc(fin);
        while ( isalnum(temp) ){
          if ( (isalnum(temp))){
            token[counter] = temp;
            counter++;
          } else {
            break;
          }
          temp = fgetc(fin);
          if(isspace(temp)){
            state = 0;
            break;
          }
        }

        //printf("Found this token %s \n", token);
        Identifier *id = &token;
        process(MyList, id);
        break;
      } else if (isspace(ch)){ // Keeping state: space to space
        state = 0;
        break;
      } else if (ch == '/'){ // State: space to comments
        state = 2;
        temp = fgetc(fin);
        while (temp != '\n'){
          temp = fgetc(fin);
          if (temp == '\n'){ // State: space to newline
            state = 4;
            break;
          }
        }
        break;
      } else if (ch == '"'){ // State: space to string
        state = 3;
        temp = fgetc(fin);
        while(temp != '"')
        temp = fgetc(fin);
        break;
      } else if(ch == '\n' || ch == '\t'){ // State: space to newline/tab
        state = 4;
        break;
      } else { // State: space to symbol
        state = 5;
        break;
      }
      case 1:
      if (isspace(ch)){ // State: word to space
        state = 0;
      } else if(ch == '"'){ // State: word to comments
        state = 3;
        temp = fgetc(fin);
        while(temp != '"')
        temp = fgetc(fin);
        break;
      } else if(ch == '\n' || ch == '\t'){ // State: word to newline
        state = 4;
        break;
      } else if(ch == '/'){ // State: word to comments
        state = 2;
        temp = fgetc(fin);
        while (temp != '\n'){
          temp = fgetc(fin);
          if (temp == '\n'){ // State: word to newline/tab
            state = 4;
            break;
          }
        }
        break;
      } else {
        if (isalpha(ch) ){ // State: space to word
          state = 1;
          int counter = 0;
          char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
          token[counter] = ch; // Add the first character
          counter++; // Increment the counter;
          temp = fgetc(fin);
          while ( isalnum(temp) ){
            if ( (isalnum(temp))){
              token[counter] = temp;
              counter++;
            } else {
              break;
            }
            temp = fgetc(fin);
            if(isspace(temp)){
              state = 0;
              break;
            }
          }
          // Process the identifier we found
          Identifier *id = &token;
          process(MyList, id);
          break;
        } else { // State: word to symbol
          state = 5;
          break;
        }

      }
      case 2:
      if (ch == '/'){ // Keeping state: comments to comments
        state = 2;
        break;
      } else if (isspace(ch)){ // State: comments to space
        state = 0;
        break;
      } else if(ch == '\n' || ch == '\t'){ // State: comments to new line
        state = 4;
        break;
      } else if(isalpha(ch)){ // State: comments to word
        state = 1;
        int counter = 0;
        char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
        token[counter] = ch; // Add the first character
        counter++; // Increment the counter;
        temp = fgetc(fin);
        while ( isalnum(temp) ){
          if ( (isalnum(temp) ) ){
            token[counter] = temp;
            counter++;
          } else {
            break;
          }
          temp = fgetc(fin);
          if(isspace(temp)){
            state = 0;
            break;
          }
        }
        // Process the token we have found
        Identifier *id = &token;
        process(MyList, id);
        break;
      } else if(ch == '"'){ // State: comments to string
        state = 3;
        temp = fgetc(fin);
        while(temp != '"')
        temp = fgetc(fin);
        break;
      } else { // State: comments to symbol
        state = 5;
        break;
      }
      case 3:
      if(ch == '"'){ // Starting or ending a string
        break;
      } else if(ch == '/'){ // State: string to comments
        state = 2;
        temp = fgetc(fin);
        while(temp != '\n'){
          temp = fgetc(fin);
          if(temp == '\n'){ // State: string to newline
            state = 4;
            break;
          }
        }
        break;
      } else if(isalpha(ch)){ // State: string to word
        state = 1;
        int counter = 0;
        char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
        token[counter] = ch; // Add the first character
        counter++; // Increment the counter;
        temp = fgetc(fin);
        while ( isalnum(temp) ){
          if ( isalnum(temp) ){
            token[counter] = temp;
            counter++;
          } else {
            break;
          }
          temp = fgetc(fin);
          if(isspace(temp)){
            state = 0;
            break;
          }
        }

        // Process the token we have found
        Identifier *id = &token;
        process(MyList, id);
        break;
      } else { // State: string to symbol
        state = 5;
        break;
      }
      case 4:
      if (isalpha(ch)){// State: new line to word
        state = 1;
        int counter = 0;
        char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
        token[counter] = ch; // Add the first character
        counter++; // Increment the counter;
        temp = fgetc(fin);
        while ( isalnum(temp) ){
          if ( isalnum(temp) ){
            token[counter] = temp;
            counter++;
          } else {
            break;
          }
          temp = fgetc(fin);
          if(isspace(temp)){
            state = 0;
            break;
          }
        }

        // Process the new token we have found
        Identifier *id = &token;
        process(MyList, id);
        break;
      } else if (isspace(ch)){ // State: new line to space
        state = 0;
        break;
      } else if (ch == '"'){ // State: newline to string
        state = 3;
        temp = fgetc(fin);
        while(temp != '"')
        temp = fgetc(fin);
        break;
      } else if (ch == '/'){ // State: newline to comments
        state = 2;
        temp = fgetc(fin);
        while(temp != '\n'){
          temp = fgetc(fin);
          if(temp == '\n'){ // Keeping state: new line to new line
            state = 4;
            break;
          }
        }
        break;
      } else { // State: new line to symbol
        state = 5;
        break;
      }
      case 5:
      if (isalpha(ch)){ // State: symbol to word
        state = 1;
        int counter = 0;
        char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
        token[counter] = ch; // Add the first character
        counter++; // Increment the counter;
        temp = fgetc(fin);
        while ( isalnum(temp) ){
          if ( isalnum(temp) ){
            token[counter] = temp;
            counter++;
          } else {
            break;
          }
          temp = fgetc(fin);
          if(isspace(temp)){
            state = 0;
            break;
          }
        }

        // Process the token we have found
        Identifier *id = &token;
        process(MyList, id);
        break;
      } else if (isspace(ch)){ // State: symbol to space
        state = 0;
        break;
      } else if (ch == '/'){ // State: symbol to comments
        state = 2;
        temp = fgetc(fin);
        while(temp != '\n'){
          temp = fgetc(fin);
          if(temp == '\n'){
            state = 4;
            break;
          }
        }
        break;
      } else if (ch == '"'){ // Symbol to string
        state = 3;
        temp = fgetc(fin);
        while(temp != '"')
        temp = fgetc(fin);
        break;
      } else if (ch == '\n' || ch == '\t' ){ // Symbol to new line/tab
        state = 4;
        temp = fgetc(fin);
        while(temp != '\n'){
          temp = fgetc(fin);
          if(temp == '\n'){
            state = 4;
            break;
          }
        }
        break;
      } else {
        break;
      }
      default:
      printf("No rules for processing character %c\n", ch );
    }
  }



// Close the file
fclose(fin);

// Redirect the result of the program to the sample file
int countList = 0;
Node * top = MyList->top;
while( countList < MyList->size){
  printf("\nIdentifier: %s, Count: %d \n", top->identifier, top->count);
  top = top->next;
  countList++;
}

return 0;
}
