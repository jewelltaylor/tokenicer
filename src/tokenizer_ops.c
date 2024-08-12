#include "tokenizer_ops.h"
#include <stdio.h>  // printf
#include <stdlib.h> // free

TokenPairToCountTable *get_stats(GList *ids) {
    TokenPairToCountTable *token_pair_counts = table_new();
    for (GList *iterator = ids; iterator != NULL && iterator->next != NULL; iterator = iterator->next) {
        TokenPair *pair = token_pair_new(*((long *)iterator->data), *((long *)iterator->next->data));

        const long value = table_lookup(token_pair_counts, pair);
        table_insert_or_update(token_pair_counts, pair, value == -1 ? 1 : value + 1);
    }
    return token_pair_counts;
}

GList *merge(GList *ids, TokenPair pair, long id) {
    GList *new_ids = NULL;
    for (GList *iterator = ids; iterator != NULL; iterator = iterator->next) {
        long new_id;
        if (iterator->next == NULL || !(pair.first_token == *(long *)iterator->data  && pair.second_token == *(long *)iterator->next->data)) {
            new_id = *((long *)iterator->data);
        } else {
            iterator = iterator->next;
            new_id = id;
        }
        new_ids = g_list_prepend(new_ids, long_new(new_id));
    }
    g_list_free_full(ids, free);
    return g_list_reverse(new_ids);
}

GList *text_to_ids(const char *text) {
    GList *ids = NULL;
    for (long i = 0; text[i] != '\0'; i++) {
        ids = g_list_prepend(ids, long_new((long)text[i]));
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

void vocab_size_save(long vocab_size, FILE * file) { fwrite(&vocab_size, sizeof(long), 1, file); }
long vocab_size_load(FILE *file) { 
    long vocab_size;
    fread(&vocab_size, sizeof(long), 1, file); 
    return vocab_size;
}

void vocab_save(char **vocab, long vocab_size, FILE *file) {
    for (long i = 256; i < vocab_size; i++) { 
        int token_length = strlen(vocab[i]) + 1;
        fwrite(&token_length, sizeof(int), 1, file);
        fwrite(vocab[i], sizeof(char), token_length, file);
    }
}

char **vocab_load(FILE *file, long vocab_size) {
    char **vocab = vocab_init(vocab_size);
    for (long i = 256; i < vocab_size; i++) { 
        int token_length;
        fread(&token_length, sizeof(int), 1, file);
        vocab[i] = (char *) malloc(token_length * sizeof(char));
        fread(vocab[i], sizeof(char), token_length, file); 
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
    free(vocab);
}
