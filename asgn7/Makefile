# Compiler and flags
CC = clang
CFLAGS = -g -Wall -Wextra -pedantic -std=c99

# Source files and output binaries
SRCS = xd.c
OBJS = $(SRCS:.c=.o)
TARGET = xd

BAD_XD_SRCS = bad_xd.c
BAD_XD_OBJS = $(BAD_XD_SRCS:.c=.o)
BAD_XD_TARGET = bad_xd

# Default rule
.PHONY: all clean

all: $(TARGET) $(BAD_XD_TARGET)

# Link the object file to create the final binary for xd
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Link the object file to create the final binary for bad_xd
$(BAD_XD_TARGET): $(BAD_XD_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files for xd
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile source files into object files for bad_xd
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET) $(BAD_XD_OBJS) $(BAD_XD_TARGET)

