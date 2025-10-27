/*
* File:     nibbler.c
*
* Purpose:  Normally files are read and written one byte at a time, but
*           these routines let us read and write files one nibble (4 bits)
*           at a time.
*/

#include "nibbler.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Purpose:  Open a file for use by nib_get_nibble() or nib_put_nibble().
*
* Using fopen(), open file "filename" with mode "mode".
* If fopen() returns NULL, then this function returns NULL.
* Allocate a NIB struct using calloc(), and initialize it:
*
*    nib->underlying_f holds the return value from fopen().
*    nib->opened_for_read is set to 1 if mode starts with 'r'.
*
* Return a pointer to the NIB.
*/
NIB *nib_open(const char *filename, const char *mode) {
  //open file w mode 
   FILE *file = fopen(filename, mode);
//check that file opened 
   if (file == NULL) {
       	return NULL;
}

//allocate memory for NIB structure
NIB *nib = calloc(1, sizeof(NIB));
if (nib == NULL) {
	fclose(file);
	return NULL;
}

//initialize NIB structure
nib->underlying_f = file;
nib->opened_for_read = (mode[0] == 'r') ? 1 : 0;
return nib;
}


/*
* Purpose:  Read a nibble from an open input file.
*
* if nib->num_nibbles > 0:
*    nib->num_nibbles = 0
*    Return nib->stored_nibble.
* else
*    int byte = fgetc(nib->underlying_f)
*    If byte is EOF then return EOF.
*    nib->stored_nibble = low nibble of the byte.
*    nib->num_nibbles = 1
*    Return high nibble of the byte.
*/
int nib_get_nibble(NIB *nib) {
   if (nib == NULL) {
	   return EOF;
   }

   //check if stored nibble is available
   if (nib->num_nibbles > 0) {
	   //reset nibble count 
	   nib->num_nibbles = 0;
	   return nib->stored_nibble;
   }

   //read a byte 
   int byte = fgetc(nib->underlying_f);
   if (byte == EOF) {
	   return EOF;
   }
   
   //extract the low nibble and store it
   nib->stored_nibble = byte & 0x0F;
   //set num_nibbles to show a nibble is stored
   nib->num_nibbles = 1;

   return (byte >> 4) & 0x0F;
}

/*
* Purpose:  Write a nibble to an open NIB.
*
* if nib->num_nibbles > 0:
*    Create a byte using nib->stored_nibble as the high nibble and the
*       parameter "nibble" as the low nibble.
*    Write the byte using fputc(nib->underlying_f).
*    nib->num_nibbles = 0
* else
*    nib->stored_nibble = nibble
*    nib->num_nibbles = 1
*/
void nib_put_nibble(int nibble, NIB *nib) {
   if (nib == NULL) {
	   return;
   }

   if (nib->num_nibbles > 0) {
	   //combine stored nibble and current nibble into a byte
	   int byte = (nib->stored_nibble << 4) | (nibble & 0x0F);
	   fputc(byte, nib->underlying_f);
	   //reset nibble count
	   nib->num_nibbles = 0;
   } else {
	   nib->stored_nibble = nibble & 0x0F;
	   nib->num_nibbles = 1;
}
}

/*
* Purpose:  Close the NIB file.
*
* If the file is opened for write and nib->num_nibbles > 0 then
*    create a byte with nib->stored_nibble as the high nibble.
*    write the byte using fputc(nib->underlying_f).
* Close file with fclose(nib->underlying_f).
*/
void nib_close(NIB *nib) {
      if (nib == NULL) {
        return;
    }


    if (nib->underlying_f != NULL) {
        if (!nib->opened_for_read && nib->num_nibbles > 0) {
            // Write the remaining nibble as the high nibble of a byte
            int byte = (nib->stored_nibble << 4) & 0xF0;
            fputc(byte, nib->underlying_f);
        }

        fclose(nib->underlying_f);
        nib->underlying_f = NULL;
    } 
}
