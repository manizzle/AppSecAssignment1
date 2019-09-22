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

test: $(MAIN_BINARY)
	./$<

clean:
	rm -rf *.o $(MAIN_BINARY)
