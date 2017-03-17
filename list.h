/*************************************************
* The data definition for the self-organizing list
* @author Gloire Rubambiza
* @version 03/13/2017
*************************************************/
Copyright (c) 2017 Gloire Rubambiza All Rights Reserved.
#include <stdlib.h>
#include <stdio.h>
#ifndef H_LIST
#define H_LIST


 // Define the datatypes to be used

 // Define a node structure with all its components
 typedef char * Identifier;
 typedef int occurence;

 struct Nodes{
   Identifier identifier;
   occurence count;
   struct Nodes * next;
 };

 typedef struct Nodes Node;


 // Define a linked-list of nodes each with components and next pointers
 struct Lists {
   Node *top;
   int size;
 };

 typedef struct Lists List;

 /**********************************************
 * Creates a new node to be inserted in the list
 ***********************************************/
 Node createnode(Identifier * id);

 /*********************
 * Initializes the list
 **********************/
 int initialize( List * list);


 /*******************************
 * Inserts a new node in the list
 ********************************/
 int insert( List * list, Node * node);

 /************************************
 * Searches for an element in the list
 ************************************/
 int search(const List * list, Node * node);

 /************************************************
 * Moves an element found to the front of the list
 ************************************************/
 int movetofront( List * list, int s_result);

#endif
