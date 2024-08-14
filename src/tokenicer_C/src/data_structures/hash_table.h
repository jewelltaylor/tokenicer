#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "token_pair.h"
#include <glib.h>
#include <stdio.h>

typedef struct TokenPairToCountTable TokenPairToCountTable;

TokenPairToCountTable *table_new();

void table_free(TokenPairToCountTable *table);

long table_lookup(TokenPairToCountTable *table, const TokenPair *pair);

void table_insert_or_update(TokenPairToCountTable *table, TokenPair *pair, long value);

long table_size(TokenPairToCountTable *table);

TokenPair *table_max(TokenPairToCountTable *table);

GList *table_keys(TokenPairToCountTable *table);

void table_print(TokenPairToCountTable *table);

void table_save(TokenPairToCountTable *table, FILE *file);

TokenPairToCountTable *table_load(FILE *file);

#endif // TABLE_H!
