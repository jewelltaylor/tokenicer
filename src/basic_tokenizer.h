#ifndef BASIC_TOKENIZER 
#define BASIC_TOKENIZER 

#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"

void get_merges(GList ** ids, TokenPairToCountTable * token_merge_table, TokenPairValuePriorityQueue * pqueue, char ** vocab, long vocab_size);

void encode(GList ** ids, TokenPairValuePriorityQueue * pqueue);

char * decode(GList * ids, char ** vocab);

#endif // BASIC_TOKENIZER_H!
