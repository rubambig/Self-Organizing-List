#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int read_file( char * filename, char **buffer){

  // Find the size of file to know how much memory
  // is needed for the allocation
  struct stat st;
  stat(filename, &st);
  int size = st.st_size;
  char ch;

  // Allocate the memory space
  *buffer = malloc(size * sizeof(char));

  //Open a new file input
  FILE *fin;
  fin = fopen(filename, "r");

  // Check that the file was opened correctly
  // Notify  the user that the file might not be in the
  // current directory
  if(fin == NULL){
    fprintf(stderr, "Error opening file named: %s\n", filename );
    exit(EXIT_FAILURE);
  }

  int totalRead = fread(*buffer, 1, size, fin );
  if (totalRead != size){
    fprintf(stderr, "Something went wrong with reading %s\n", filename );
  }
  printf("Read %d bytes of characters\n", totalRead);

  //Close the file
  // Return the number of bytes read
  fclose(fin);
  return totalRead;
}

int write_file(char * filename, char *buffer, int size){
  char lastChar;
  //Open a new file output
  FILE *fout;
  fout = fopen(filename, "w");

  //Check that the file was opened correctly
  if(fout == NULL){
    fprintf(stderr, "Error opening a new file named: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  //Write to the file character by character
  while( size >= 0){
    lastChar = buffer[size];    // Point to the end of the buffer
    printf("Current %c \n", lastChar);
    fputc(lastChar, fout);
    size--;
  }

  // Close file output
  fclose(fout);
  return 0;

}
