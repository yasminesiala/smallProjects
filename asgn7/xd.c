#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // Added this to avoid the isprint error
#include <errno.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
    // Exit if more than one command line argument is provided
    if (argc > 2) {
        return 1;
    }

    // Open the file using open(), not fopen()
    int input = STDIN_FILENO; // default to stdin
    if (argc == 2) {
        input = open(argv[1], O_RDONLY);
        if (input == -1) {
            // Silent error, just return 1 without printing anything
            return 1;
        }
    }

    unsigned char buffer[BYTES_PER_LINE];
    ssize_t bytes_read;  // `ssize_t` to match `read()` return type
    size_t offset = 0;
    
    // Process the file in chunks of 16 bytes
    while ((bytes_read = read(input, buffer, BYTES_PER_LINE)) > 0) {
        printf("%08zx: ", offset); // Print the offset

        // Print the hexadecimal values
        for (size_t i = 0; i < (size_t)bytes_read; i++) {  // Cast to size_t
            if (i < (size_t)bytes_read) {
                printf("%02x", buffer[i]);
            } else {
                printf("  "); // Print spaces for missing bytes
            }
            // Add space between every two hexadecimal digits
            if ((i + 1) % 2 == 0) {
                printf(" ");
            }
        }

        // Print the ASCII values
        printf(" ");
        for (size_t i = 0; i < (size_t)bytes_read; i++) {  // Cast to size_t
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf("."); 
            }
        }

        printf("\n");
        offset += bytes_read;
    }

    // Close the file descriptor if it's not stdin
    if (input != STDIN_FILENO) {
        close(input);
    }

    return 0;
}

