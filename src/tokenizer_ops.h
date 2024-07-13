#ifndef TOKENIZER_OPS
#define TOKENIZER_OPS

#include "structs/table.h"
#include <glib.h>

#define VOCAB_SIZE 267 

GList * merge(GList * ids, TokenPair pair, long id);

void get_stats(GList * ids, TokenPairToCountTable * token_pair_counts);

void buffer_to_ids(char * buffer, GList ** pids, long sequence_length);

void get_initial_vocab(char ** vocab);

void vocab_free(char ** vocab, long vocab_size);

#endif // TOKENIZER_OPS_H!
