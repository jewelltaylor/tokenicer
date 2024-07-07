#include <glib.h> // open 
#include <stdio.h> // open 

#include "general.h" 
#include "table.h" 

struct TokenPairToCountTable {
    GHashTable * table;
};

gboolean token_pair_equal(gconstpointer a, gconstpointer b) {
    const TokenPair *first_pair = a;
    const TokenPair *second_pair = b;
    return (first_pair->first_token == second_pair->first_token) && (first_pair->second_token == second_pair->second_token);
}

guint token_pair_hash(gconstpointer a) {
    const TokenPair *pair = a;
    return g_int_hash(&pair->first_token) ^ g_int_hash(&pair->second_token);
}

TokenPairToCountTable * table_new() {
    TokenPairToCountTable * table = malloc(sizeof(TokenPairToCountTable));
    GHashTable *glib_table = g_hash_table_new_full(token_pair_hash, token_pair_equal, free, free); 
    table->table = glib_table;
    return table; 
}

void table_free(TokenPairToCountTable * table) {
    GHashTable * glib_table = table->table;
    g_hash_table_destroy(glib_table);
    free(table);
}

long table_lookup(TokenPairToCountTable * table, TokenPair * pair) {
    long * lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        return *lookup;
    } else {
        return (long) -1;
    }
}

void table_insert_or_update(TokenPairToCountTable * table, TokenPair * pair, long value) {
    if (value < 0) {
        perror("Values must be 0 or greater");
        return;
    }
    long * lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        g_hash_table_replace(table->table, pair, long_new(value));
    } else {
        g_hash_table_insert(table->table, pair, long_new(value));
    }
}

void table_max(TokenPairToCountTable * table, TokenPair * max_pair) {
    GList *keys = NULL;
    table_keys(table, &keys);
    GList *iter = keys; 

    long max_value = -1;

    while (iter != NULL) {
        TokenPair *pair = (TokenPair *)iter->data;
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
        return;
    }

    return;
}

void table_keys(TokenPairToCountTable * table, GList ** keys_pointer) {
    GList *keys = g_hash_table_get_keys(table->table);
    *keys_pointer = keys;
}

void table_print(TokenPairToCountTable* table) {
    GList *keys = g_hash_table_get_keys(table->table);
    GList *iter = keys;

    while (iter != NULL) {
        TokenPair *key = iter->data;
        long value = table_lookup(table, key);
        printf("(%ld, %ld) => %ld\n", key->first_token, key->second_token, value);
        iter = iter->next;
    }

    g_list_free(keys);
}
