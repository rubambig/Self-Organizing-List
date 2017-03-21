/***********************************************
* Defines the functionality of different methods
* @author Gloire Rubambiza
* @version 03/13/2017
* Copyright (c) 2017 Gloire Rubambiza All Rights Reserved.
* **********************************************/

#include "list.h"
#include <string.h>
#define FIRST 1
#define SECOND 2
#define NOMATCH -1

/*int main(){
  List l;
  int initstatus = initialize(&l);


  Identifier myId = "Gloire";

  Node myNode = createnode(&myId);
  printf("The first node is %s\n", myNode.identifier);

  int ins1 = insert(&l, &myNode);

  printf("Status of first insert is %d \n\n", ins1);

  Identifier myId2 = "Rubambiza";
  Node myNode2 = createnode(&myId2);

  int ins2 = insert(&l, &myNode2);
  printf("The second node is %s\n", myNode2.identifier);


  printf("Status of second insert is %d \n\n ", ins2);

  Identifier myId3 = "Balegamire";
  Node myNode3 = createnode(&myId3);

  int ins3 = insert(&l, &myNode3);
  printf("The third node is %s\n", myNode3.identifier);


  printf("Status of third insert is %d \n\n ", ins3);

  Identifier myId4 = "Elie";
  Node myNode4 = createnode(&myId4);

  int ins4 = insert(&l, &myNode4);
  printf("The fourth node is %s\n", myNode4.identifier);


  printf("Status of four insert is %d \n\n ", ins4);

  Identifier myId5 = "Nsesi";
  Node myNode5 = createnode(&myId5);

  int ins5 = insert(&l, &myNode5);
  printf("The fifth node is %s\n", myNode5.identifier);


  printf("Status of fifth insert is %d \n\n ", ins5);

  printf("Performing searches\n");
  int result1 = search(&l, &myNode);
  printf("Search 1 result is %d \n\n", result1);
  int result2 = search(&l, &myNode2);
  printf("Search 2 result is %d \n", result2);
  int result3 = search(&l, &myNode3);
  printf("Search 3 result is %d \n", result3);

  int result4 = search(&l, &myNode4);
  printf("Search 4 result is %d \n", result4);
  int result5 = search(&l, &myNode5);
  printf("Search 5 result is %d \n\n\n", result5);

  int move1 = movetofront(&l, result1);
  printf("Move to front result 2 is %d\n\n", move1 );

  int move2 = movetofront(&l, result2);
  printf("Move to front result 2 is %d\n\n", move2 );

  int move3 = movetofront(&l, result3);
  printf("Move to front result 2 is %d\n\n", move3 );

  int move4 = movetofront(&l, result4);
  printf("Move to front result 2 is %d\n\n", move4 );

  int move5 = movetofront(&l, result5);
  printf("Move to front result 2 is %d\n\n", move5 );

  return 0;

}*/

/*****************************************
 * Processes a token found in file scanning
 * @param token the new token
 * ***************************************/
void process( List * list, Identifier *id){

  // Search if the identifier exists in the list
  Node * associate = createnode(id);
  int index = search(list, associate);

  if(index < 0){
    insert(list, associate);
    printf("The list top is now %s\n", list->top->identifier);
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
    //printf("The new size is %d\n", list->size);
    //printf("The first element is %s\n", list->top->identifier);
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

  printf("Something went wrong bud! \n");
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
     printf("This list is empty! No searches allowed!\n");
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
     printf("Entered no man's land\n\n");
        // Not found in the first or second, loop through
        while(top->next != NULL){

          if (strcmp(top->next->identifier, node->identifier) == 0){
            counter++;
            top->next->count++;
            return counter;
          } /*else {
            continue;
          }*/
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
   /*if(list->size >= 2){
     Node * third = list->top->next->next;
   }*/

   printf("Current is starting at %s\n", current->identifier);

   // Handle the special case if the match is the last node.
   if(index == list->size){

     // Loop through to find the last element
     while(counter < list->size){
       counter++;
       if(counter == list->size){
         current->next->next = list->top;
         list->top = current->next;
         current->next = NULL;
         printf("The new top is %s \n", list->top->identifier);
         return 0;
       }
       current = current->next;
     }

   } else if(index == 2 && list->top->next->next == NULL){

     current->next->next = list->top;
     list->top = current->next;
     printf("Handled the case when it's only two elements\n");
     printf("The new top is %s \n", list->top->identifier);
     return 0;

   } else if(index == 2 && list->top->next->next != NULL){

     current->next = list->top->next->next;
     second->next = current;
     list->top = second;
     printf("Handled the case of second match \n");
     printf("The new top is %s \n", list->top->identifier);
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
         printf("Handled a regular case \n");
         printf("The new top is %s \n", list->top->identifier);
         return 0;
       }
       current = current->next;
     }
   }
   return -1;
 }
