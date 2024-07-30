#ifndef BASIC_TOKENIZER
#define BASIC_TOKENIZER

#include "structs/pqueue.h"
#include "structs/table.h"

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

#endif // BASIC_TOKENIZER_H!
