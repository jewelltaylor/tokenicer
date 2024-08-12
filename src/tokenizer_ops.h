#ifndef TOKENIZER_OPS
#define TOKENIZER_OPS

#include "data_structures/hash_table.h"
#include <glib.h>

#define VOCAB_SIZE 267
GList *merge(GList *ids, TokenPair pair, long id);

TokenPairToCountTable *get_stats(GList *ids);

GList *text_to_ids(const char *text);

char **vocab_init(long vocab_size);

void vocab_save(char **vocab, long vocab_size, FILE *file);

char **vocab_load(FILE *file, long vocab_size);

void vocab_size_save(long vocab_size, FILE *file);

long vocab_size_load(FILE *file);

void vocab_free(char **vocab, long vocab_size);

#endif // TOKENIZER_OPS_H!
