/*
* Program:      compress
*
* Purpose:      Compress a file.
*
* Usage:        compress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  compress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Compress FILE *fin into the NIB *nib.  Assumes that fin already has been
* opened by fin = fopen(...) and that nib already has been opened by nib =
* nib_open(...).
*
* compress(FILE *fin, NIB *nib):
*    loop
*       Use fgetc(fin) to get an int ch.
*
*       If ch is EOF then break
*
*       If ch is in the table of Fig. 2:
*          Convert ch into its corresponding nibble from Fig. 2.
*          Write the nibble to nib using nib_put_nibble(nibble, nib).
*       else
*           Write a 0 nibble using nib_put_nibble(nibble, nib).
*           Write the high nibble of ch using nib_put_nibble(nibble, nib).
*           Write the low nibble of ch using nib_put_nibble(nibble, nib).
*/
static const int conversion_table[256] = {
    [' '] = 0x1, ['e'] = 0x2, ['t'] = 0x3, ['n'] = 0x4,
    ['r'] = 0x5, ['o'] = 0x6, ['a'] = 0x7, ['i'] = 0x8,
    ['s'] = 0x9, ['d'] = 0xA, ['l'] = 0xB, ['h'] = 0xC,
    ['c'] = 0xD, ['f'] = 0xE, ['p'] = 0xF
};

void compress(FILE *fin, NIB *nib) {
   if (fin == NULL || nib == NULL) {
	   fprintf(stderr, "Error: Invalid input/output file.\n");
	   return;
   }

   int ch;
   while ((ch = fgetc(fin)) != EOF) {
	   if (ch >= 0 && ch < 256 && conversion_table[ch] != 0) {
		   int nibble = conversion_table[ch];
		   nib_put_nibble(nibble, nib);
	   } else {
		   nib_put_nibble(0x0, nib);
		   nib_put_nibble((ch >> 4) & 0xF, nib);
		   nib_put_nibble(ch & 0xF, nib);
	}
}
}

/*
* Usage:  ./compress INFILE -o OUTFILE
*
* Confirm that there are four command-line arguments.
* Confirm that argv[2] is "-o".
* Treat argv[1] as the name of the input file.
* Treat argv[3] as the name of the output file.
* Open the input file using fopen(), and report any error.
* Open the output file using nib_open(), and report any error.
* Call compress().
* Close the files.
*/
int main(int argc, char **argv) {
if (argc != 4) {
        fprintf(stderr, "Usage: ./compress INFILE -o OUTFILE\n");
        return 1;
    }

    // Ensure the second argument is "-o"
    if (strcmp(argv[2], "-o") != 0) {
        fprintf(stderr, "Error: Second argument must be '-o'\n");
        return 1;
    }

    // Assign input and output filenames
    const char *input_filename = argv[1];
    const char *output_filename = argv[3];

    // Open the input file
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Could not open input file '%s'\n", input_filename);
        return 1;
    }

    // Open the output file using nib_open
    NIB *output_file = nib_open(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Could not open output file '%s'\n", output_filename);
        fclose(input_file);
        return 1;
    }

    // Call the compress function
    compress(input_file, output_file);

    // Close the files
    fclose(input_file);
    nib_close(output_file);

    return 0;
}
