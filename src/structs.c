#include <stdlib.h> // free 
#include <glib.h> // open 

#include "structs.h" 


guint token_pair_hash(gconstpointer key) {
    const TokenPair *pair = key;
    return g_int_hash(&pair->first_token) ^ g_int_hash(&pair->second_token);
}

gboolean token_pair_equal(gconstpointer a, gconstpointer b) {
    const TokenPair *first_pair = a;
    const TokenPair *second_pair = b;
    return (first_pair->first_token == second_pair->first_token) && (first_pair->second_token == second_pair->second_token);
}

TokenPair *token_pair_new(int first_token, int second_token) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    pair->first_token = first_token;
    pair->second_token = second_token;
    return pair;
}

int *int_new(int value) {
    int *p = malloc(sizeof(int));
    *p = value;
    return p;
}

void token_pair_free(gpointer pair) {
    free(pair);
}

void value_free(gpointer value) {
    free(value);
}
