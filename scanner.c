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
  int main(){
    // Initialize all global variables
    printf("We're getting started\n\n");
      int state = 0;
      char ch, temp;
      char * listing[10000];
      int tempcount = 0;

      List * MyList = initialize();
      printf("Initialized list with size %d\n\n", MyList->size);


      FILE * fin = fopen("sample.c", "r");

      while ( ch = fgetc(fin), ch != EOF){
          printf("Found char %c \n", ch);
          printf("The state is %d \n", state);
          switch (state) {
  	  case 0:
  	    if (isalpha(ch)){ // Handle if we find a new identifier
  	       state = 1; // Change state
           printf("Changin state from space to word \n\n");
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
           listing[tempcount] = token;
           tempcount++;
	         Identifier *id = &token;
	         process(MyList, id);
           break;
  	  } else if (isspace(ch)){
  	       state = 0;
           printf("Keeping state from space to space\n\n");
           break;
  	  } else if (ch == '/'){
  	     state = 2;
         printf("Changing state from space to comments \n\n");
         temp = fgetc(fin);
         while (temp != '\n'){
           temp = fgetc(fin);
           if (temp == '\n'){
             state = 4;
             printf("Changing state from space to newline/tab \n\n" );
             break;
           }
         }
         break;
  	  } else if (ch == '"'){
        state = 3;
        printf("Changing state from space to string quotes");
        temp = fgetc(fin);
        while(temp != '"')
          temp = fgetc(fin);
        break;
      } else if(ch == '\n' || ch == '\t'){
        state = 4;
        printf("Changing state from space to new line or tab \n\n");
        break;
      } else {
        state = 5;
        printf("State is now %d, changing from space to symbol\n\n", state);
        break;
      }
  	  case 1:
  	    if (isspace(ch)){
          state = 0;
          printf("Changing state from word to space\n\n");
          break;                    // Switching from letter to letter, unlikely.
        } else if(ch == '"'){
  	      state = 3;
          printf("Changing state from letter to comments "" \n\n");
  	      temp = fgetc(fin);
          while(temp != '"')
            temp = fgetc(fin);      // Switching from letter to string quotes
  	      break;
  	   } else if(ch == '\n' || ch == '\t'){
         state = 4;
         printf("Changing state from letter to new line or tab \n\n");
         break;
       } else if(ch == '/'){
         state = 2;
         printf("Word to Comments \n\n");
         temp = fgetc(fin);
         while (temp != '\n'){
           temp = fgetc(fin);
           if (temp == '\n'){
             state = 4;
             printf("Changing state from letter to newline/tab \n\n");
             break;
           }
         }
         break;
       } else {
         printf("\n WE HAVE %c here\n\n", ch);
         if (isalpha(ch) ){
           state = 1; // Change state
           printf("Changin state from space to word \n\n");
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
           printf("Found this token %s \n", token);
           Identifier *id = &token;
	         process(MyList, id);
           listing[tempcount] = token;
           tempcount++;
           break;
         } else {
           state = 5;
           printf("State is now %d, changing from word to symbol\n\n", state);
           break;
         }

       }
  	  case 2:
  	    if (ch == '/'){
          state = 2;
          printf("Keeping state: Comments to comments \n\n" );
          break;
  	    } else if (isspace(ch)){
  	      state = 0;
          printf("Changing state from comments to space\n\n");
  	      break;
  	   } else if(ch == '\n' || ch == '\t'){
         state = 4;
         printf("Changing state from comments to new line or tab \n\n");
         break;
  	   } else if(isalpha(ch)){
         state = 1;
         int counter = 0;
         printf("Changing state from comments to word \n\n");
         char * token = malloc(MAX * sizeof(char)); // Assume token len < 50
         token[counter] = ch; // Add the first character
         counter++; // Increment the counter;
         temp = fgetc(fin);
         while ( isalnum(temp) ){
           //temp = fgetc(fin);
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
         printf("Found this token %s \n", token);
         Identifier *id = &token;
         process(MyList, id);
         listing[tempcount] = token;
         tempcount++;
         break;
       } else if(ch == '"'){
         state = 3;
         printf("Changing state from comments to string quotes \n\n");
         temp = fgetc(fin);
         while(temp != '"')
            temp = fgetc(fin);      // Switching from letter to string quotes
         break;
       } else {
         state = 5;
         printf("State is now %d, changing from comments to symbol\n\n", state);
         break;
       }
      case 3:
        if(ch == '"'){
          printf("Keeping state: string quotes to string\n\n" );
          break;
        } else if(ch == '/'){
           state = 2;
           printf("String quotes to comments\n\n");
           temp = fgetc(fin);
           while(temp != '\n'){
             temp = fgetc(fin);
             if(temp == '\n'){
               state = 4;
               printf("Changing state from string quotes to newline \n\n");
               break;
             }
           }
           break;
         } else if(isalpha(ch)){
           state = 1;
           int counter = 0;
           printf("String quotes to word\n\n");
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
           printf("Found this token %s \n", token);
           Identifier *id = &token;
	         process(MyList, id);
           listing[tempcount] = token;
           tempcount++;
           break;
         } else {
           state = 5;
           printf("State is now %d, changing from quotes to symbol\n\n", state);
           break;
         }
        case 4:
          if (isalpha(ch)){
            state = 1;
            printf("Changing state from new line to identifier \n\n");
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
            printf("Found this token %s \n", token);
            Identifier *id = &token;
 	          process(MyList, id);
            listing[tempcount] = token;
            tempcount++;
            break;
          } else if (isspace(ch)){
            state = 0;
            printf("New line to space \n\n");
            break;
          } else if (ch == '"'){
            state = 3;
            printf("New line to string quotes \n\n");
            temp = fgetc(fin);
            while(temp != '"')
               temp = fgetc(fin);      // Switching from newline to string quotes
            break;
          } else if (ch == '/'){
            state = 2;
            printf("Changing state from new line to comments \n\n");
            temp = fgetc(fin);
            while(temp != '\n'){
              temp = fgetc(fin);
              if(temp == '\n'){
                state = 4;
                printf("Keeping state: new line to new line \n\n");
                break;
              }
            }
            break;
          } else {
            state = 5;
            printf("State is now %d, changing from newline to symbol\n\n", state);
            break;
          }
          case 5:
            if (isalpha(ch)){
              state = 1;
              printf("Symbol to word\n\n");

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
              printf("Found this token %s \n", token);
              listing[tempcount] = token;
              tempcount++;
              Identifier *id = &token;
   	          process(MyList, id);
              break;
            } else if (isspace(ch)){
              state = 0;
              printf("Symbol to space\n\n");
              break;
            } else if (ch == '/'){
              state = 2;
              printf("Symbol to comments\n\n");
              temp = fgetc(fin);
              while(temp != '\n'){
                temp = fgetc(fin);
                if(temp == '\n'){
                  state = 4;
                  printf("Keeping state: new line to new line \n\n");
                  break;
                }
              }
              break;
            } else if (ch == '"'){
              state = 3;
              printf("Symbol to string quotes \n\n");
              temp = fgetc(fin);
              while(temp != '"')
                 temp = fgetc(fin);      // Switching from symbol to string quotes
              break;
            } else if (ch == '\n' || ch == '\t' ){
              state = 4;
              printf("Symbol to newline \n\n");
              temp = fgetc(fin);
              while(temp != '\n'){
                temp = fgetc(fin);
                if(temp == '\n'){
                  state = 4;
                  printf("Keeping state: new line to newline \n\n");
                  break;
                }
              }
              break;
            } else {
              break;
            }
            default:
              printf("Something fishy!\n" );
  	}
      }
      printf("\n\n File scanning done \n");
      int i;
      /*for(i =0; i < 500; i++){
        printf("Token number %d is %s\n", i, listing[i]);
      }*/
      int countList = 0;
      Node * top = MyList->top;
      //printf("First node is %s\n", top->identifier);
      //top = top->next;
      //printf("Second node is %s\n", top->identifier);

      while( countList < MyList->size){
	       printf("The node here is %s, with count %d\n\n", top->identifier, top->count);
	       top = top->next;
         countList++;
      }
      return 0;
  }
