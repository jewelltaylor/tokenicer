#ifndef PQUEUE_H
#define PQUEUE_H

#include "token_pair.h"
#include <stdio.h>
#include <glib.h>

typedef struct TokenPairValuePriorityQueue TokenPairValuePriorityQueue;

TokenPairValuePriorityQueue *pqueue_new();

void pqueue_free(TokenPairValuePriorityQueue *pqueue);

void pqueue_remove(TokenPairValuePriorityQueue *pqueue);

const TokenPairCount *pqueue_peek(TokenPairValuePriorityQueue *pqueue);

unsigned long pqueue_length(TokenPairValuePriorityQueue *pqueue);

void pqueue_insert(TokenPairValuePriorityQueue *pqueue, TokenPairCount *token_pair_count);

long pqueue_size(TokenPairValuePriorityQueue *pqueue);

void pqueue_save(TokenPairValuePriorityQueue *pqueue, FILE *file);

TokenPairValuePriorityQueue *pqueue_load(FILE *file);

#endif // PQUEUE_H!
