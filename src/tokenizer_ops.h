#ifndef TOKENIZER_OPS
#define TOKENIZER_OPS

#include "structs/table.h"
#include <glib.h>

#define VOCAB_SIZE 267
GList *merge(GList *ids, TokenPair pair, long id);

TokenPairToCountTable *get_stats(GList *ids);

GList *text_to_ids(const char *text);

char **vocab_init(long vocab_size);

void vocab_free(char **vocab, long vocab_size);

#endif // TOKENIZER_OPS_H!
