#include "tokenizer_ops.h"
#include "structs/table.h"
#include <stdio.h>  // printf
#include <stdlib.h> // free

void get_stats(GList *ids, TokenPairToCountTable *token_pair_counts) {
    for (GList *iterator = ids; iterator != NULL && iterator->next != NULL; iterator = iterator->next) {
        const long *first_token = (long *)iterator->data;
        const long *second_token = (long *)iterator->next->data;
        TokenPair *pair = token_pair_new(*first_token, *second_token);

        const long value = table_lookup(token_pair_counts, pair);
        table_insert_or_update(token_pair_counts, pair, value == -1 ? 1 : value + 1);
    }
}

GList *merge(GList *ids, TokenPair pair, long id) {
    GList *new_ids = NULL;
    for (GList *iterator = ids; iterator != NULL; iterator = iterator->next) {
        long new_id;
        const long *first_token = (long *)iterator->data;
        if (iterator->next == NULL) {
            new_id = *first_token;
        } else {
            const long *second_token = (long *)iterator->next->data;
            if (pair.first_token == *first_token && pair.second_token == *second_token) {
                iterator = iterator->next;
                new_id = id;
            } else {
                new_id = *first_token;
            }
        }
        new_ids = g_list_prepend(new_ids, long_new(new_id));
    }
    g_list_free_full(ids, free);
    return g_list_reverse(new_ids);
}

GList *buffer_to_ids(const char *buffer, long sequence_length) {
    GList *ids = NULL;
    for (long i = 0; i < sequence_length; i++) {
        ids = g_list_prepend(ids, long_new((long)buffer[i]));
    }
    return g_list_reverse(ids);
}

char **vocab_init(long vocab_size) {
    char **vocab = malloc(vocab_size * sizeof(char *));
    for (long i = 0; i < 256; i++) {
        vocab[i] = (char *)malloc(2 * sizeof(char));

        if (vocab[i] == NULL) {
            perror("Error allocating initial vocab");
            exit(EXIT_FAILURE);
        }

        vocab[i][0] = (char)i;
        vocab[i][1] = '\0';
    }
    return vocab;
}

void vocab_free(char **vocab, long vocab_size) {
    for (long i = 0; i < vocab_size; i++) {
        if (vocab[i] == NULL) {
            break;
        }

        free(vocab[i]);
    }
}
