#ifndef TABLE_H
#define TABLE_H 

#include <glib.h>
#include "general.h"

typedef struct TokenPairToIntTable TokenPairToIntTable; 

TokenPairToIntTable * table_new();

void table_free(TokenPairToIntTable * table);

int table_lookup(TokenPairToIntTable * table, TokenPair * pair);

void table_insert_or_update(TokenPairToIntTable * table, TokenPair * pair, int value);

void table_keys(TokenPairToIntTable * table, GList ** keys);

void table_print(TokenPairToIntTable* table);

#endif // TABLE_H!
