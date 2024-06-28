#include <glib.h> // open 
#include <stdio.h> // open 

#include "general.h" 
#include "table.h" 

struct TokenPairToIntTable {
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

TokenPairToIntTable * table_new() {
    TokenPairToIntTable * table = malloc(sizeof(TokenPairToIntTable));
    GHashTable *token_merge_table= g_hash_table_new_full(token_pair_hash, token_pair_equal, free, free); 
    table->table = token_merge_table;
    return table; 
}

void table_free(TokenPairToIntTable * table) {
    GHashTable * glib_table = table->table;
    g_hash_table_destroy(glib_table);
    free(table);
}

int table_lookup(TokenPairToIntTable * table, TokenPair * pair) {
    int * lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        return *lookup;
    } else {
        return -1;
    }
}

void table_insert_or_update(TokenPairToIntTable * table, TokenPair * pair, int value) {
    int * lookup = g_hash_table_lookup(table->table, pair);
    if (lookup != NULL) {
        g_hash_table_replace(table->table, pair, int_new(value));
    } else {
        g_hash_table_insert(table->table, pair, int_new(value));
    }
}

void table_keys(TokenPairToIntTable * table, GList ** keys_pointer) {
    GList *keys = g_hash_table_get_keys(table->table);
    *keys_pointer = keys;
}

void table_print(TokenPairToIntTable* table) {
    GList *keys = g_hash_table_get_keys(table->table);
    GList *iter = keys;

    while (iter != NULL) {
        TokenPair *key = iter->data;
        int value = table_lookup(table, key);
        printf("(%d, %d) => %d\n", key->first_token, key->second_token, value);
        iter = iter->next;
    }

    g_list_free(keys);
}
