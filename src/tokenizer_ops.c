#include <stdlib.h> // free 
#include <stdio.h> // printf
#include "tokenizer_ops.h"
#include "structs/table.h"

void get_stats(GList * ids, TokenPairToCountTable * token_pair_counts) {
    for (GList * iterator = ids; iterator !=  NULL && iterator->next != NULL; iterator = iterator->next) { 
        long *first_token = (long *) iterator->data;
        long *second_token = (long *) iterator->next->data;
        TokenPair * pair = token_pair_new(*first_token, *second_token);

        long value = table_lookup(token_pair_counts, pair);

        if (value == -1) {
            table_insert_or_update(token_pair_counts, pair, 1);
        } else {
            table_insert_or_update(token_pair_counts, pair, value + 1);
        }
    }
}

void merge(GList * ids, GList ** new_pids, TokenPair pair, long id) {
    for (GList * iterator = ids; iterator != NULL && iterator->next != NULL; iterator = iterator->next) {
        long * new_id = malloc(sizeof(long));
        long *first_token = (long *) iterator->data;
        long *second_token = (long *) iterator->next->data;
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

void buffer_to_ids(unsigned char * buffer, GList ** pids, long sequence_length) { 
    for (long i = 0; i < sequence_length; i++) {
        long * id = malloc(sizeof(int));
        *id = (long) buffer[i];
        *pids = g_list_prepend(*pids, id);
    }
    *pids = g_list_reverse(*pids);
    return;
}

void get_initial_vocab(char * vocab[VOCAB_SIZE]) {
    for (long i = 0; i < 256; i++) {
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
    for (long i = 0; i < VOCAB_SIZE; i++) {
        if (vocab[i] == NULL || vocab[i] == 0) {
            break;
        }

        free(vocab[i]);
    }
}

