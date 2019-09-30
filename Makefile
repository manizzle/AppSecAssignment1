CC=clang
#CC=~/Development/afL/afl-clang
MAIN_BINARY=spell_check
OBJS=spell.o test.o dictionary.o
CFLAGS=-I ./hashmap -fprofile-instr-generate -fcoverage-mapping
LDFLAGS=-Wall -fprofile-instr-generate -fcoverage-mapping
VPATH = .:./hashmap

hashmap/%.o : hashmap/%.c
	$(CC) $(CFLAGS) $< -c -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(MAIN_BINARY): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm -lpthread

test: $(MAIN_BINARY)
	./$(MAIN_BINARY) test1.txt wordlist.txt
	#xcrun llvm-profdata merge -o testcov.profdata default.profraw
	#xcrun llvm-cov show ./$(MAIN_BINARY) -instr-profile=testcov.profdata spell.c

clean:
	rm -rf *.o $(MAIN_BINARY) testcov.profdata default.profraw
