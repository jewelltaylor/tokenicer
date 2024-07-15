#ifndef TABLE_H
#define TABLE_H

#include "general.h"
#include <glib.h>

typedef struct TokenPairToCountTable TokenPairToCountTable;

TokenPairToCountTable *table_new();

void table_free(TokenPairToCountTable *table);

long table_lookup(TokenPairToCountTable *table, const TokenPair *pair);

void table_insert_or_update(TokenPairToCountTable *table, TokenPair *pair, long value);

void table_max(TokenPairToCountTable *table, TokenPair *max_pair);

void table_keys(TokenPairToCountTable *table, GList **keys);

void table_print(TokenPairToCountTable *table);

#endif // TABLE_H!
