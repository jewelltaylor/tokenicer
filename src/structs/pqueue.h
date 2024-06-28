#ifndef PQUEUE_H
#define PQUEUE_H

#include <glib.h>
#include "general.h"

void pop(TokenPairCount * token_pair_count, GQueue * queue);
void insert(TokenPairCount * token_pair_count, GQueue * queue);

#endif // PQUEUE_H!
