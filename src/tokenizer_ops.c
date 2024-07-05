#include <stdlib.h> // free 
#include <stdio.h> // printf
#include "tokenizer_ops.h"

void get_stats(GList * ids, TokenPairToIntTable * token_pair_counts) {
    for (GList * iterator = ids; iterator !=  NULL && iterator->next != NULL; iterator = iterator->next) { 
        int *first_token = (int *) iterator->data;
        int *second_token = (int *) iterator->next->data;
        TokenPair * pair = token_pair_new(*first_token, *second_token);

        int value = table_lookup(token_pair_counts, pair);

        if (value == -1) {
            table_insert_or_update(token_pair_counts, pair, 1);
        } else {
            table_insert_or_update(token_pair_counts, pair, value + 1);
        }
    }
}

void merge(GList * ids, GList ** new_pids, TokenPair pair, int id) {
    for (GList * iterator = ids; iterator != NULL && iterator->next != NULL; iterator = iterator->next) {
        int * new_id = malloc(sizeof(int));
        int *first_token = (int *) iterator->data;
        int *second_token = (int *) iterator->next->data;
        if (pair.first_token == *first_token && pair.second_token == *second_token) {
            iterator = iterator->next;
            *new_id = id;
        } else {
            *new_id = *first_token;
        }
        *new_pids = g_list_prepend(*new_pids, new_id);
    }
    *new_pids = g_list_reverse(*new_pids);
}

void buffer_to_ids(unsigned char * buffer, GList ** pids, int sequence_length) { 
    for (int i = 0; i < sequence_length; i++) {
        int * id = malloc(sizeof(int));
        *id = (int) buffer[i];
        *pids = g_list_prepend(*pids, id);
    }
    *pids = g_list_reverse(*pids);
    return;
}

void get_max_token_pair_count(TokenPairToIntTable * token_pair_counts, TokenPairCount * max_token_pair_count) {
    GList *keys = NULL;
    table_keys(token_pair_counts, &keys);
    GList *iter = keys; 

    TokenPair *max_pair = NULL;
    int max_value = -1;

    while (iter != NULL) {
        TokenPair *pair = (TokenPair *)iter->data;
        int value = table_lookup(token_pair_counts, pair);

        if (value > max_value) {
            max_pair = pair; 
            max_value = value;
        }
        iter = iter->next;
    }
    g_list_free(keys);

    if (max_pair == NULL) {
        perror("Error getting max token pair");
        return;
    }
    max_token_pair_count->pair = *max_pair;
    max_token_pair_count->count = max_value;

    return;
}

void get_initial_vocab(char * vocab[VOCAB_SIZE]) {
    for (int i = 0; i < 256; i++) {
        vocab[i] = (char *) malloc(2 * sizeof(char));

        if (vocab[i] == NULL) {
            perror("Error allocating initial vocab");
            exit(EXIT_FAILURE);
        }

        vocab[i][0] = (char) i;
        vocab[i][1] = '\0';
    }
}

void vocab_free(char * vocab[VOCAB_SIZE]) {
    for (int i = 0; i < VOCAB_SIZE; i++) {
        if (vocab[i] == NULL || vocab[i] == 0) {
            break;
        }

        free(vocab[i]);
    }
}

