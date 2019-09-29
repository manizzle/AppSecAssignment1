#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <assert.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"


void test_check_word_normal()
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    assert(check_word(correct_word, hashtable));
    assert(!check_word(punctuation_word_2, hashtable));
    // Test here: What if a word begins and ends with "?
}

void test_check_words_normal()
{
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


int main() {
    test_check_word_normal();
    test_check_words_normal();
}