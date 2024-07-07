#ifndef TOKENIZER_OPS
#define TOKENIZER_OPS

#include "structs/table.h"
#include <glib.h>

#define VOCAB_SIZE 267 

void merge(GList * ids, GList ** new_pids, TokenPair pair, int id);

void get_stats(GList * ids, TokenPairToCountTable * token_pair_counts);

void buffer_to_ids(unsigned char * buffer, GList ** pids, int sequence_length);

void get_initial_vocab(char * vocab[VOCAB_SIZE]);

void vocab_free(char * vocab[VOCAB_SIZE]);

#endif // TOKENIZER_OPS_H!
