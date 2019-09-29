#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void iterate_hashtable(hashmap_t hashtable[]);
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);
bool check_word(const char* word, hashmap_t hashtable[]);
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]);
int strip_nl(char* word);


void lower_case(char* word) {
	for (int i = 0; i < strlen(word); i++) {
		word[i] = tolower(word[i]);
	}
}

char* remove_punctuation(char* word) {
	int start = 0, word_len = strlen(word);
	while (start < word_len) {
		if (ispunct(word[start])) {
			start++;
		}
		else {
			break;
		}
	}

	if (start == word_len) {
		return NULL;
	}

	for (int i = strlen(word+start)-1; i > start; i--) {
		if (ispunct(word[i])) {
			word[i] = 0;
		}
		else {
			break;
		}
	}
	return (word+start);
}

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
	int num_misspelled = 0;
	char *line = NULL, *tmp_str = NULL;
	size_t len = 0;
	ssize_t nread;
	int i = 0;
	char* x_misspelled = (char*)misspelled;

	while ((nread = getline(&line, &len, fp)) != -1) {
		i = 0;
		char *token = strtok(line, " ");
	    while (token) {
			token = remove_punctuation(token);
			if (!strip_nl(token)) {
				token = strtok(NULL, " ");
				continue;
			}
			if (strlen(token) > LENGTH || strlen(token) == 0) {
				token = strtok(NULL, " ");
				continue;
			}
			if (!check_word(token, hashtable)) {
				misspelled[num_misspelled] = calloc(strlen(token), 1);
				strncpy(misspelled[num_misspelled], token, strlen(token));
				num_misspelled++;
			}
	        token = strtok(NULL, " ");
	    }
    }
    free(line);
    return num_misspelled;
}

bool check_word(const char* word, hashmap_t hashtable[]) {
	int bucket = hash_function(word);
	hashmap_t cursor = hashtable[bucket];
	int word_len = strlen(word);
	while (cursor != NULL) {
		if (!strncmp(word, cursor->word, word_len)) {
			return true;
		}
		cursor = cursor->next;
	}
	char *tmp = calloc(word_len, 1);
	strncpy(tmp, word, word_len);
	lower_case(tmp);
	bucket = hash_function(tmp);
	cursor = hashtable[bucket];
	while (cursor != NULL) {
		if (!strncmp(tmp, cursor->word, word_len)) {
			free(tmp);
			return true;
		}
		cursor = cursor->next;
	}

	free(tmp);
	return false;
}

int strip_nl(char* word) {
	int word_len = strlen(word);
	for (int i = 0; i < word_len; i++) {
		if (word[i] == '\n') {
			word[i] = 0;
			return i;
		}
	}
	return word_len;
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	hashmap_t new_node = NULL, tmp_node = NULL;
	int bucket = 0;

	for (int i = 0; i < HASH_SIZE; i++) {
		hashtable[i] = NULL;
	}

	stream = fopen(dictionary_file, "r");

	if (stream == NULL) {
		perror("fopen failed the file does not exist");
		return false;
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
		len = strip_nl(line);
		if (len > LENGTH) {
			len = LENGTH;
		}
        new_node = calloc(sizeof(node), 1);
        new_node->next = NULL;
        strncpy(new_node->word, line, len);
        bucket = hash_function(line);
        if (hashtable[bucket] == NULL) {
			hashtable[bucket] = new_node;
        }
        else {
			tmp_node = hashtable[bucket];
			while (tmp_node->next) {
				tmp_node = tmp_node->next;
			}
			tmp_node->next = new_node;
		}
    }
    free(line);
    fclose(stream);
	return false;
}

void iterate_hashtable(hashmap_t hashtable[]) {
	for (int i = 0; i < HASH_SIZE; i++) {
		if (hashtable[i]) {
			hashmap_t curr_node = hashtable[i];
			while (curr_node) {
				//printf("%d %s\n", i, curr_node->word);
				curr_node = curr_node->next;
			}
		}
	}
}

void free_hashtable(hashmap_t hashtable[]) {
	hashmap_t tmp;
	for (int i = 0; i < HASH_SIZE; i++) {
		if (hashtable[i]) {
			hashmap_t curr_node = hashtable[i];
			while (curr_node) {
				tmp = curr_node->next;
				free(curr_node);
				//printf("%d %s\n", i, curr_node->word);
				curr_node = tmp;
			}
		}
	}
}
