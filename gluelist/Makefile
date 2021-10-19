CC=gcc
CFLAGS=-fstack-protector -ggdb
OBJ= test.o gllist.o 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o test

