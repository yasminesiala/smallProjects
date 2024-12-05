#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
    if (argc > 2) {
        return 1;
    }

    int input = STDIN_FILENO;
    if (argc == 2) {
        input = open(argv[1], O_RDONLY);
        if (input == -1) {
            perror("Failed to open file");
            return 1;
        }
    }

    unsigned char buffer[BYTES_PER_LINE];
    ssize_t bytes_read;
    size_t offset = 0;
    size_t buffer_index = 0;

    while ((bytes_read = read(input, buffer + buffer_index, BYTES_PER_LINE - buffer_index)) > 0) {
        buffer_index += bytes_read;

        if (buffer_index == BYTES_PER_LINE) {
            printf("%08x: ", (unsigned int)offset);  // Use %08x for printing int offsets

            for (size_t i = 0; i < BYTES_PER_LINE; i++) {
                printf("%02x", buffer[i]);
                if ((i + 1) % 2 == 0) {
                    printf(" ");
                }
            }

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
            buffer_index = 0;
        }
    }

    if (buffer_index > 0) {
        printf("%08x: ", (unsigned int)offset);

        for (size_t i = 0; i < BYTES_PER_LINE; i++) {
            if (i < buffer_index) {
                printf("%02x", buffer[i]);
            } else {
                printf("  ");
            }
            if ((i + 1) % 2 == 0) {
                printf(" ");
            }
        }

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

    if (input != STDIN_FILENO) {
        close(input);
    }
    return 0;
}

