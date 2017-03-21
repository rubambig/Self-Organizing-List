/*********************************************************
* Defines the functionality of different methods
* @author Gloire Rubambiza
* @version 03/13/2017
* @filename: list.c
* Project developed as part of the System Programming
* class(CIS 361) at Grand Valley State University.
* Copyright (c) 2017 Gloire Rubambiza All Rights Reserved.
* *******************************************************/

#include "list.h"
#include <string.h>
#define FIRST 1
#define SECOND 2
#define NOMATCH -1

/******************************************
 * Processes a token found in file scanning
 * @param token the new token
 * ***************************************/
void process( List * list, Identifier *id){

  // Search if the identifier exists in the list
  // Otherwise insert into the list
  Node * associate = createnode(id);
  int index = search(list, associate);

  if(index < 0){
    insert(list, associate);
  } else {
    movetofront(list, index);
  }
}

/***************************************
* Initializes the list and its head
* @param list the new list to be created
****************************************/
List * initialize(){
  List * MyList = malloc(sizeof(List));
  // Check that we are not initializing a non-empty list
  MyList->top = NULL;
  MyList->size = 0;

  return MyList;

}

/*********************************************
* Creates a new node from the given identifier
* Sets its counter to 1
* @param id the newly found identifier
***********************************************/
Node * createnode(Identifier * id){

  // Allocate space for the new node
  Node * newnode = malloc(sizeof(Node));
  newnode->identifier = malloc(sizeof(Identifier));
  strcpy(newnode->identifier, *id);
  newnode->count = 1;
  newnode->next = NULL;
  return newnode;
}

/*********************************
* Inserts a new node in the list
* @param list the current list
* Remember to increment the occurence if a match is hit
********************************/
int insert( List * list, Node * node){

  // Check that the top of the list is not empty
  if (list->top == NULL){

    list->top = node;
    list->size++;
    return 0;

  } else if(list->top->next == NULL){ // If the second node is empty
    list->top->next = node;
    list->size++;
    return 0;

  } else {
    Node * traverse = list->top; // Starts from the top node.

    while(traverse->next != NULL){

      // Move one spot down the list.
      traverse = traverse->next;

      // Make the null pointer point to the given node.
      if(traverse->next == NULL){
        traverse->next = node;
        list->size++;
        return 0;
      }
    }

  }

  printf("Something went awry with the insert! \n");
  return -1;

}

/***********************************************
 * Searches for an element in the list
 * Should be constant for most searches(ideally)
 * @param list the given list
 **********************************************/
int search(const List * list, Node * node){
    int counter = 1;

    // Check that we are not searching an empty list
    if (list->top == NULL){
     return NOMATCH;
    }

   // Point to the top of the list
   // If the element is at the beginning return right away
   Node * top = list->top;
   if(strcmp(top->identifier, node->identifier) == 0){
      top->count++;
	    return FIRST;

   } else if (top->next != NULL ){
      if(strcmp(top->next->identifier, node->identifier) == 0){
        top->next->count++;
  	    return SECOND;
      }

   }
   if (top->next == NULL ) {
     return NOMATCH;
   } else {
        // Not found in the first or second, loop through
        while(top->next != NULL){

          if (strcmp(top->next->identifier, node->identifier) == 0){
            counter++;
            top->next->count++;
            return counter;
          }

          top = top->next;
          counter++;
        }
   }
   return NOMATCH;


}

/*************************************************
 * Moves an element found to the front of the list
 * Changes the top of the list
 * @param list the current list
 ************************************************/
 int movetofront(List * list, int index){
   int counter = 1;
   Node * current = list->top;
   Node * first = list->top; // To be used 2 elements, with a third present
   Node * second = list->top->next;

   // Handle the special case if the match is the last node.
   if(index == list->size){

     // Loop through to find the last element
     while(counter < list->size){
       counter++;
       if(counter == list->size){
         current->next->next = list->top;
         list->top = current->next;
         current->next = NULL;
         return 0;
       }
       current = current->next;
     }

   } else if(index == 2 && list->top->next->next == NULL){

     current->next->next = list->top;
     list->top = current->next;
     return 0;

   } else if(index == 2 && list->top->next->next != NULL){

     current->next = list->top->next->next;
     second->next = current;
     list->top = second;
     return 0;

   } else { // Handle all the other cases

     Node * dummy = malloc(sizeof(Node));

     while(counter < index){
       counter++;
       if(counter == index){
         dummy->identifier = malloc(sizeof(Identifier));
         strcpy(dummy->identifier, current->next->identifier);
         dummy->count = current->next->count;
         current->next = current->next->next;
         dummy->next = list->top;
         list->top = dummy;
         return 0;
       }
       current = current->next;
     }
   }
   return -1;
 }
