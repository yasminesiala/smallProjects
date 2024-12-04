#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
    //exit if more than one command line argument provided 
    if (argc > 2) {
        return 1;
    }

    int input = STDIN_FILENO;  // Use file descriptor instead of FILE pointer
    if (argc == 2) {
        input = open(argv[1], O_RDONLY);
        if (input == -1) {
            perror("Failed to open file");
            return 1;
        }
    }  

    //initialize variables:
    unsigned char buffer[BYTES_PER_LINE];
    ssize_t bytes_read;
    size_t offset = 0;
    
    // To accumulate bytes until we have 16 bytes
    size_t buffer_index = 0;
    
    while ((bytes_read = read(input, buffer + buffer_index, BYTES_PER_LINE - buffer_index)) > 0) {
        buffer_index += bytes_read;

        // When we have a full 16 bytes, print it
        if (buffer_index == BYTES_PER_LINE) {
            printf("%08zx: ", offset); // print the offset in hexadecimal

            // Print hexadecimal column
            for (size_t i = 0; i < BYTES_PER_LINE; i++) {
                printf("%02x", buffer[i]);
                if ((i + 1) % 2 == 0) {
                    printf(" ");
                }
            }

            // Print ASCII column
            printf(" ");
            for (size_t i = 0; i < BYTES_PER_LINE; i++) {
                if (isprint(buffer[i])) {
                    printf("%c", buffer[i]);
                } else {
                    printf(".");
                }
            }
            printf("\n");

            offset += BYTES_PER_LINE;
            buffer_index = 0; // Reset buffer for next line
        }
    }

    // Handle remaining bytes if they are less than 16
    if (buffer_index > 0) {
        printf("%08zx: ", offset); // print the offset in hexadecimal

        // Print hexadecimal column
        for (size_t i = 0; i < BYTES_PER_LINE; i++) {
            if (i < buffer_index) {
                printf("%02x", buffer[i]);
            } else {
                printf("  "); // print spaces for missing bytes
            }
            if ((i + 1) % 2 == 0) {
                printf(" ");
            }
        }

        // Print ASCII column
        printf(" ");
        for (size_t i = 0; i < buffer_index; i++) {
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    // Clean up
    if (input != STDIN_FILENO) {
        close(input);
    }
    return 0;
}

