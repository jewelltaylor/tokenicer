#ifndef BPE_H
#define BPE_H

#include "data_structures/hash_table.h"
#include "data_structures/priority_queue.h"

typedef struct {
    TokenPairToCountTable *token_merge_table;
    TokenPairValuePriorityQueue *pqueue;
    char **vocab;
    long vocab_size;
} Tokenizer;

Tokenizer *tokenizer_train(const char *text, long vocab_size);

long *tokenizer_encode(Tokenizer *tokenizer, const char *text, long *ids_array_length);

void tokenizer_free_array(long *ids_array);

char *tokenizer_decode(Tokenizer *tokenizer, long *ids_array, long ids_array_length);

void tokenizer_save(Tokenizer *tokenizer, char *filename);

Tokenizer *tokenizer_load(char *filename);

void tokenizer_free(Tokenizer *tokenizer);

#endif // BPE_H!
