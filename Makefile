CC=clang
MAIN_BINARY=spell_check
OBJS=spell.o test.o dictionary.o
CFLAGS=-I ./hashmap
VPATH = .:./hashmap

hashmap/%.o : hashmap/%.c
	$(CC) $(CFLAGS) $< -c -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(MAIN_BINARY): $(OBJS)
	$(CC) -o $@ $^

test: dictionary.o spell.o test_main.o
	gcc -Wall -o test_main test_main.o spell.o dictionary.o -lm -lpthread
	./test_main

clean:
	rm -rf *.o $(MAIN_BINARY)
