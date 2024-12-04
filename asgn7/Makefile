# Compiler and flags
CC = clang
CFLAGS = -g -Wall -Wextra -pedantic -std=c99

# Source files and output binary
SRCS = xd.c
OBJS = $(SRCS:.c=.o)
TARGET = xd

# Default rule
.PHONY: all clean

all: $(TARGET)

# Link the object file to create the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

