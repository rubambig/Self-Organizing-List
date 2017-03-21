/*********************************************************
* The data definition for the self-organizing list
* Provides skeleton for operations on the linked-list
* @author Gloire Rubambiza
* @version 03/13/2017
* @filename: list.h
* Project developed as part of the System Programming
* class(CIS 361) at Grand Valley State University.
* Copyright (c) 2017 Gloire Rubambiza All Rights Reserved.
**********************************************************/

#include <stdlib.h>
#include <stdio.h>
#ifndef H_LIST
#define H_LIST


 // Define the datatypes to be used
 typedef char * Identifier;
 typedef int occurence;

// Define a node structure with all its components
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
 Node * createnode(Identifier * id);

 /*********************
 * Initializes the list
 **********************/
 List * initialize();

 /*************************
  * Processes a given token
  * ***********************/
 void process( List * list, Identifier *id);


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
