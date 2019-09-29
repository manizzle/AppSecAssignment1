#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "spell.h"

extern hashmap_t hashtable[HASH_SIZE];
char *misspelled[MAX_MISSPELLED] = {0};

//  ./spell_check a_tale_of_two_cities.txt wordlist.txt
int main(int argc, char** argv) {
	int misspelled_count = 0;
	FILE* stream = NULL;
	if (argc != 3) {
		printf("%s [file to check spelling] [dictionary]\n", argv[0]);
		return 0;
	}
	load_dictionary(argv[2], hashtable);
	iterate_hashtable(hashtable);

	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("fopen failed the file does not exist");
		return false;
	}
	misspelled_count = check_words(stream, hashtable, misspelled);
	for (int i = 0; i < misspelled_count; i++) {
		//printf("misspelled word: %s\n", misspelled[i]);
		free(misspelled[i]);
	}
	free_hashtable(hashtable);
	return 0;
}
