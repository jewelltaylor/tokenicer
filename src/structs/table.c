#include <glib.h>  // open
#include <stdio.h> // open

#include "general.h"
#include "table.h"

struct TokenPairToCountTable {
    GHashTable *table;
};

gboolean token_pair_equal(gconstpointer a, gconstpointer b) {
    const TokenPair *first_pair = a;
    const TokenPair *second_pair = b;
    return (first_pair->first_token == second_pair->first_token) &&
           (first_pair->second_token == second_pair->second_token);
}

guint token_pair_hash(gconstpointer a) {
    const TokenPair *pair = a;
    return g_int_hash(&pair->first_token) ^ g_int_hash(&pair->second_token);
}

TokenPairToCountTable *table_new() {
    TokenPairToCountTable *table = malloc(sizeof(TokenPairToCountTable));
    GHashTable *glib_table = g_hash_table_new_full(token_pair_hash, token_pair_equal, free, free);
    table->table = glib_table;
    return table;
}

void table_free(TokenPairToCountTable *table) {
    GHashTable *glib_table = table->table;
    g_hash_table_destroy(glib_table);
    free(table);
}

long table_lookup(TokenPairToCountTable *table, const TokenPair *pair) {
    const long *lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        return *lookup;
    } else {
        return (long)-1;
    }
}

void table_insert_or_update(TokenPairToCountTable *table, TokenPair *pair, long value) {
    if (value < 0) {
        perror("Values must be 0 or greater");
        return;
    }
    const long *lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        g_hash_table_replace(table->table, pair, long_new(value));
    } else {
        g_hash_table_insert(table->table, pair, long_new(value));
    }
}

TokenPair *table_max(TokenPairToCountTable *table) {
    GList *keys = table_keys(table);
    GList *iter = keys;
    TokenPair *max_pair = malloc(sizeof(TokenPair));

    long max_value = -1;

    while (iter != NULL) {
        const TokenPair *pair = (TokenPair *)iter->data;
        long value = table_lookup(table, pair);

        if (value > max_value) {
            *max_pair = *pair;
            max_value = value;
        }
        iter = iter->next;
    }
    g_list_free(keys);

    if (max_pair == NULL) {
        perror("Error getting max token pair");
        exit(EXIT_FAILURE);
    }

    return max_pair;
}

GList *table_keys(TokenPairToCountTable *table) { return g_hash_table_get_keys(table->table); }

void table_print(TokenPairToCountTable *table) {
    GList *keys = g_hash_table_get_keys(table->table);
    GList *iter = keys;

    while (iter != NULL) {
        const TokenPair *key = iter->data;
        long value = table_lookup(table, key);
        printf("(%ld, %ld) => %ld\n", key->first_token, key->second_token, value);
        iter = iter->next;
    }

    g_list_free(keys);
}
