#ifndef TOKENIZER_OPS
#define TOKENIZER_OPS

#include "structs/table.h"
#include <glib.h>

#define VOCAB_SIZE 267
void merge(GList *ids, GList **new_ids, TokenPair pair, long id);

void get_stats(GList *ids, TokenPairToCountTable *token_pair_counts);

GList *buffer_to_ids(const char *buffer, long sequence_length);

char **vocab_init(long vocab_size);

void vocab_free(char **vocab, long vocab_size);

#endif // TOKENIZER_OPS_H!
