#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
    int input = (argc == 2) ? open(argv[1], O_RDONLY) : 0;
    unsigned char buffer[BYTES_PER_LINE];
    ssize_t bytes_read;
    size_t offset = 0, buffer_index = 0;

    if (argc > 2 || (input == -1 && argc == 2)) return 1;

    while ((bytes_read = read(input, buffer + buffer_index, BYTES_PER_LINE - buffer_index)) > 0) {
        buffer_index += bytes_read;
        if (buffer_index == BYTES_PER_LINE) {
            printf("%08zx: ", offset);
            for (size_t i = 0; i < BYTES_PER_LINE; i++) {
                printf("%02x", buffer[i]);
                if ((i + 1) % 2 == 0) printf(" ");
            }
            printf(" ");
            for (size_t i = 0; i < BYTES_PER_LINE; i++) {
                printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
            }
            printf("\n");
            offset += BYTES_PER_LINE;
            buffer_index = 0;
        }
    }

    if (buffer_index > 0) {
        printf("%08zx: ", offset);
        for (size_t i = 0; i < BYTES_PER_LINE; i++) {
            if (i < buffer_index) printf("%02x", buffer[i]);
            else printf("  ");
            if ((i + 1) % 2 == 0) printf(" ");
        }
        printf(" ");
        for (size_t i = 0; i < buffer_index; i++) {
            printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
        }
        printf("\n");
    }

    if (input) close(input);
    return 0;
}

