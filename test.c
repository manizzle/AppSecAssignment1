#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dictionary.h"

void iterate_hashtable(hashmap_t hashtable[]);
void free_hashtable(hashmap_t hashtable[]);

extern hashmap_t hashtable[HASH_SIZE];
char *misspelled[MAX_MISSPELLED] = {0};

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

void test_check_word_normal() {
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    assert(check_word(correct_word, hashtable));
    assert(!check_word(punctuation_word_2, hashtable));
    // Test here: What if a word begins and ends with "?
}

void test_check_words_normal() {
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    assert(test);
    assert(strcmp(misspelled[0], expected[0]) == 0);
    assert(strcmp(misspelled[1], expected[1]) == 0);
    assert(strcmp(misspelled[2], expected[2]) == 0);
}

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

	test_check_word_normal();
    test_check_words_normal();
	return 0;
}
