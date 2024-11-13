CC = clang
CFLAGS = -g

OBJECTS = tree.o unique.o unittests.o

.PHONY: all
all: unique unittests

unique: unique.o tree.o
	$(CC) $(OBJECTS) -o unique

unittests: unittests.o tree.o
	$(CC) $(OBJECTS) -o unittests

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

unique.o: unique.c
	$(CC) $(CFLAGS) -c unique.c


unittests.o: unittests.c
	$(CC) $(CFLAGS) -c unittests.c

.PHONY: clean
clean:
	rm -f *.o unique unittests
