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

GList *tokenizer_encode(const char *text, Tokenizer *tokenizer);

char *tokenizer_decode(GList *ids, Tokenizer *tokenizer);

void tokenizer_free(Tokenizer *tokenizer);

#endif // BPE_H!
