#ifndef BASIC_TOKENIZER 
#define BASIC_TOKENIZER 

#include "structs/table.h"
#include "tokenizer_ops.h"

void get_merges(GList ** ids, long n_merges, TokenPairToCountTable * token_merge_table, char * vocab[VOCAB_SIZE]);

#endif // BASIC_TOKENIZER_H!
