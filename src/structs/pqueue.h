#ifndef PQUEUE_H
#define PQUEUE_H

#include <glib.h>
#include "general.h"

typedef struct TokenPairValuePriorityQueue TokenPairValuePriorityQueue;

TokenPairValuePriorityQueue * pqueue_new();

void pqueue_free(TokenPairValuePriorityQueue * pqueue);

TokenPairCount * pqueue_remove(TokenPairValuePriorityQueue * pqueue);

unsigned long pqueue_length(TokenPairValuePriorityQueue * pqueue);

void pqueue_insert(TokenPairValuePriorityQueue * pqueue,TokenPairCount * token_pair_count);

#endif // PQUEUE_H!
