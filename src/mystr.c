#include "mystr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_first_word(const char* input) {
    if (input == NULL || *input == '\0') {
        return NULL;
    }
    while (*input == ' ') {
        input++;
    }
    if (*input == '\0') {
        return NULL;
    }

    size_t firstWordLength = 0;
    const char* startOfFirstWord = input;

    while (*input != '\0' && *input != ' ') {
        input++;
        firstWordLength++;
    }

    char* firstWord = (char*)malloc((firstWordLength + 1) * sizeof(char));
    if (firstWord == NULL) {
        fprintf(stderr, "Can't allocate the memory\n");
        exit(EXIT_FAILURE);
    }

    strncpy(firstWord, startOfFirstWord, firstWordLength);
    firstWord[firstWordLength] = '\0';

    return firstWord;
}

char* get_second_word(const char* input) {
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    while (*input != '\0' && *input != ' ') {
        input++;
    }

    while (*input == ' ') {
        input++;
    }

    if (*input == '\0') {
        return NULL;
    }

    size_t secondWordLength = 0;
    const char* startOfSecondWord = input;

    while (*input != '\0' && *input != ' ') {
        input++;
        secondWordLength++;
    }

    char* secondWord = (char*)malloc((secondWordLength + 1) * sizeof(char));
    if (secondWord == NULL) {
        fprintf(stderr, "Can't allocate the memory\n");
        exit(EXIT_FAILURE);
    }

    strncpy(secondWord, startOfSecondWord, secondWordLength);
    secondWord[secondWordLength] = '\0';

    return secondWord;
}