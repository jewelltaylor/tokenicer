#ifndef STRUCTS_H
#define STRUCTS_H

#include <glib.h>

typedef struct {
    int first_token;
    int second_token;
} TokenPair;

typedef struct {
    TokenPair pair;
    int count;
} TokenPairCount;

guint token_pair_hash(gconstpointer key);

gboolean token_pair_equal(gconstpointer a, gconstpointer b);

TokenPair* token_pair_new(int first_token, int second_token);

int* int_new(int value);

void token_pair_free(gpointer pair);

void value_free(gpointer value);

#endif // !STRUCTS_H
