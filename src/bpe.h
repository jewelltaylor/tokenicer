#ifndef BPE_H
#define BPE_H 

#include "data_structures/priority_queue.h"
#include "data_structures/hash_table.h"

typedef struct {
    GList *ids;
    TokenPairToCountTable *token_merge_table;
    TokenPairValuePriorityQueue *pqueue;
    char **vocab;
    long vocab_size;
} Tokenizer;

Tokenizer *tokenizer_train(const char *text, long vocab_size);

GList *tokenizer_encode(Tokenizer *tokenizer, const char *text);

char *tokenizer_decode(Tokenizer *tokenizer, GList *ids);

void tokenizer_save(Tokenizer *tokenizer, char *filename);

// Tokenizer *tokenizer_load(Tokenizer *tokenizer, const char *filename);

void tokenizer_free(Tokenizer *tokenizer);

#endif // BPE_H!
