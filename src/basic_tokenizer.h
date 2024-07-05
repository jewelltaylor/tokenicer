#ifndef BASIC_TOKENIZER 
#define BASIC_TOKENIZER 

#include "tokenizer_ops.h"

void get_merges(GList ** ids, int n_merges, TokenPairToIntTable * token_merge_table, char * vocab[VOCAB_SIZE]);

#endif // BASIC_TOKENIZER_H!
