#ifndef BASIC_TOKENIZER 
#define BASIC_TOKENIZER 

#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"

void get_merges(GList ** ids, long n_merges, TokenPairToCountTable * token_merge_table, TokenPairValuePriorityQueue * pqueue, char * vocab[VOCAB_SIZE]);

void encode(GList ** ids, TokenPairValuePriorityQueue * pqueue);

char * decode(GList * ids, char * vocab[VOCAB_SIZE]);

#endif // BASIC_TOKENIZER_H!
