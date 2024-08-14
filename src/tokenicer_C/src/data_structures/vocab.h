#include <stdio.h>  // printf
#include <stdlib.h> // free
//
char **vocab_init(long vocab_size);

void vocab_save(char **vocab, long vocab_size, FILE *file);

char **vocab_load(FILE *file, long vocab_size);

void vocab_size_save(long vocab_size, FILE *file);

long vocab_size_load(FILE *file);

void vocab_free(char **vocab, long vocab_size);
