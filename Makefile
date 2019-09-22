CC=clang

%.o : %.c
	$(CC) $< -c -o $@

spell: spell.o
	$(CC) -o $@ $< 

test: spell
	./$<

clean:
	rm -rf *.o spell
