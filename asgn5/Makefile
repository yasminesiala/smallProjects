CC = clang
CFLAGS = -g

OBJS = nibbler.o unittests.o compress.o decompress.o

.PHONY: all clean

all: unittests compress decompress

unittests: unittests.o nibbler.o
	$(CC) $(CFLAGS) unittests.o nibbler.o -o unittests

compress: compress.o nibbler.o
	$(CC) $(CFLAGS) compress.o nibbler.o -o compress

decompress: decompress.o nibbler.o
	$(CC) $(CFLAGS) decompress.o nibbler.o -o decompress

nibbler.o: nibbler.c
	$(CC) $(CFLAGS) -c nibbler.c

unittests.o: unittests.c
	$(CC) $(CFLAGS) -c unittests.c

compress.o: compress.c
	$(CC) $(CFLAGS) -c compress.c

decompress.o: decompress.c
	$(CC) $(CFLAGS) -c decompress.c

clean:
	rm -f $(OBJS) unittests compress decompress
