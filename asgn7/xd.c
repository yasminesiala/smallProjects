#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <errno.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
	//exit if more than one command line argument provided 
	if (argc > 2) {
		return 1;
	}

	FILE *input = stdin;
	if (argc == 2) { 
		input = fopen(argv[1], "rb");
		if (!input) {
			return 1;
		}
	}	

	//initialize variables:
	unsigned char buffer[BYTES_PER_LINE];
	size_t bytes_read;
	size_t offset = 0;
	
	while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, input)) > 0) {
		printf("%08x: ", offset); //print the offset

		//print hexadecimal column
		for (size_t i = 0; i < BYTES_PER_LINE; i++) {
			if (i < bytes_read) {
				printf("%02x", buffer[i]);
			} else {
				printf("  "); //print spaces for missing bytes
			}
			//add space between groups of two bytes 
			if ((i + 1) % 2 == 0) {
				printf(" ");
			}
		}

		//print ASCII column
		printf(" ");
		for (size_t i = 0; i < bytes_read; i++) {
			if (isprint(buffer[i])) {
				printf("%c", buffer[i]);
			} else {
				printf("."); 
			}
		}

		printf("\n");

		offset += bytes_read;
	}

	//clean up
	if (input != stdin) {
		fclose(input);
		return 0;
	}
}


