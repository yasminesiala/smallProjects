/*
* Program:      decompress
*
* Purpose:      Decompress a file that was compressed with "compress".
*
* Usage:        decompress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  decompress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Decompress NIB *nib into the FILE *fout.  Assumes that nib already has been
* opened by nib = nib_open(...) and that fout already has been opened by
* fout = fopen(...).
*
* decompress(NIB *nib, FILE *fout):
*    loop
*       read a nibble using nib_get_nibble(nib)
*       if the nibble is EOF then break
*
*       if the nibble > 0 then
*          Convert the nibble into its corresponding byte using Fig. 4
*          Write the byte using fputc(fout)
*       else
*          read nibble1 using nib_get_nibble(nib)
*          if the nibble1 == EOF then break
*
*          read nibble2 using nib_get_nibble(nib)
*          if the nibble2 == EOF then break
*
*          Create a byte with
*             nibble1 as the high nibble and nibble2 as the low nibble
*
*          Write the byte using fputc(fout)
*/
void decompress(NIB *nib, FILE *fout) {
int nibble, nibble1, nibble2;
    
    // Mapping nibble values to their corresponding characters from Fig. 4
    char lookup[] = {
        0,  // 0 is unused, as it combines two nibbles
        ' ', // 1 → ' '
        'e', // 2 → 'e'
        't', // 3 → 't'
        'n', // 4 → 'n'
        'r', // 5 → 'r'
        'o', // 6 → 'o'
        'a', // 7 → 'a'
        'i', // 8 → 'i'
        's', // 9 → 's'
        'd', // 10 → 'd'
        'l', // 11 → 'l'
        'h', // 12 → 'h'
        'c', // 13 → 'c'
        'f', // 14 → 'f'
        'p'  // 15 → 'p'
    };
    
    while (1) {
        // Read a nibble
        nibble = nib_get_nibble(nib);
        
        // If the nibble is EOF, break the loop
        if (nibble == EOF) {
            break;
        }
        
        // If nibble > 0, map it to the corresponding character and write to the file
        if (nibble > 0) {
            // Map the nibble to a character and write it to the output file
            fputc(lookup[nibble], fout);
        } else {
            // Read the next two nibbles to create a byte
            nibble1 = nib_get_nibble(nib);
            if (nibble1 == EOF) {
                break;
            }
            
            nibble2 = nib_get_nibble(nib);
            if (nibble2 == EOF) {
                break;
            }
            
            // Combine nibble1 and nibble2 to create the byte (using high and low nibbles)
            unsigned char byte = (nibble1 << 4) | nibble2;
            
            // Write the byte to the output file
            fputc(byte, fout);
        }
    }
}

/*
* Usage:  ./decompress INFILE -o OUTFILE
*
* Confirm that there are four command-line arguments.
* Confirm that argv[2] is "-o".
* Treat argv[1] as the name of the input file.
* Treat argv[3] as the name of the output file.
* Open the input file using nib_open(), and report any error.
* Open the output file using fopen(), and report any error.
* Call decompress().
* Close the files.
*/
int main(int argc, char **argv) {
    // Check for correct number of arguments
    if (argc != 4) {
	    print_usage();
    }

    if (strcmp(argv[2], "-o") != 0) {
	    print_usage();
    } 

    const char *input_filename = argv[1];
    const char *output_filename = argv[3];

    NIB *nib = nib_open(input_filename, "r");
    if (nib == NULL) {
	    fprintf(stderr, "Error opening input file: %s\n", input_filename);
	    exit(1);
    }

    FILE *fout = fopen(output_filename, "w");
    if (fout == NULL) {
	    fprintf(stderr, "Error opening output file: %s\n", output_filename);
	    nib_close(nib);
	    exit(1);
   }

   decompress(nib, fout);
  nib_close(nib);
 fclose(fout);

return 0; 


}
