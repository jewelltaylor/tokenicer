#include "bpe.h"
#include "data_structures/hash_table.h"
#include "data_structures/priority_queue.h"
#include "data_structures/token_pair.h"
#include "data_structures/vocab.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

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
        if (iterator->next == NULL ||
            !(pair.first_token == *(long *)iterator->data && pair.second_token == *(long *)iterator->next->data)) {
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

Tokenizer *tokenizer_train(const char *text, long vocab_size) {

    GList *ids = text_to_ids(text);
    TokenPairToCountTable *token_merge_table = table_new();
    TokenPairValuePriorityQueue *pqueue = pqueue_new();
    char **vocab = vocab_init(vocab_size);

    for (long i = 256; i < vocab_size; i++) {
        TokenPairToCountTable *token_pair_counts = get_stats(ids);
        TokenPair *max_pair = table_max(token_pair_counts);
        table_insert_or_update(token_merge_table, max_pair, i);

        pqueue_insert(pqueue, token_pair_count_new(max_pair->first_token, max_pair->second_token, i));

        ids = merge(ids, *max_pair, i);

        int token_str_len = strlen(vocab[max_pair->first_token]) + strlen(vocab[max_pair->second_token]) + 1;
        vocab[i] = malloc(token_str_len * sizeof(char));
        strcpy(vocab[i], vocab[max_pair->first_token]);
        strcat(vocab[i], vocab[max_pair->second_token]);

        table_free(token_pair_counts);
    }

    g_list_free_full(ids, free);
    Tokenizer *tokenizer = malloc(sizeof(Tokenizer));
    *tokenizer = (Tokenizer){token_merge_table, pqueue, vocab, vocab_size};
    return tokenizer;
}

long *g_list_to_array(GList *ids) {
    long ids_length = (long) g_list_length(ids); 

    long *ids_array = malloc(sizeof(long) * ids_length); 

    GList *iterator = ids;
    for (long i = 0; i < ids_length; i++) {
        ids_array[i] = *(long *) iterator->data;
        iterator = iterator->next;
    }
    g_list_free_full(ids, free);

    return ids_array;
}

long *tokenizer_encode(Tokenizer *tokenizer, const char *text, long *ids_array_length) {
    GList *ids = text_to_ids(text);
    while (g_list_length(ids) >= 2 && pqueue_length(tokenizer->pqueue) != 0) {
        TokenPairToCountTable *table = get_stats(ids);

        while (pqueue_length(tokenizer->pqueue) && table_lookup(table, &pqueue_peek(tokenizer->pqueue)->pair) == -1)
            pqueue_remove(tokenizer->pqueue);

        if (pqueue_length(tokenizer->pqueue)) {
            const TokenPairCount *head = pqueue_peek(tokenizer->pqueue);
            TokenPairCount *pair_count =
                token_pair_count_new(head->pair.first_token, head->pair.second_token, head->count);
            ids = merge(ids, pair_count->pair, pair_count->count);
            free(pair_count);
        }
        table_free(table);
    }
    *ids_array_length = (long) g_list_length(ids);
    return g_list_to_array(ids);
}

void tokenizer_free_array(long *ids_array) {
    free(ids_array);
}

char *tokenizer_decode(Tokenizer *tokenizer, long *ids_array, long ids_array_length) {
    GString *str = g_string_new("");
    for (long i = 0; i < ids_array_length; i++) {
        g_string_append(str, tokenizer->vocab[ids_array[i]]);
    }

    char *result = g_strdup(str->str);
    g_string_free(str, TRUE);
    return result;
}

void tokenizer_save(Tokenizer *tokenizer, char *filepath) {
    FILE *file = fopen(filepath, "wb");

    if (file == NULL) {
        perror("Error opening load file");
        exit(EXIT_FAILURE);
    }

    pqueue_save(tokenizer->pqueue, file);
    table_save(tokenizer->token_merge_table, file);
    vocab_size_save(tokenizer->vocab_size, file);
    vocab_save(tokenizer->vocab, tokenizer->vocab_size, file);
    fclose(file);
}

Tokenizer *tokenizer_load(char *filepath) {
    FILE *file = fopen(filepath, "rb");

    if (file == NULL) {
        perror("Error opening load file");
        exit(EXIT_FAILURE);
    }

    Tokenizer *tokenizer = malloc(sizeof(Tokenizer));
    TokenPairValuePriorityQueue *pqueue = pqueue_load(file);
    tokenizer->pqueue = pqueue;
    TokenPairToCountTable *table = table_load(file);
    tokenizer->token_merge_table = table;
    long vocab_size = vocab_size_load(file);
    tokenizer->vocab_size = vocab_size;
    char **vocab = vocab_load(file, tokenizer->vocab_size);
    tokenizer->vocab = vocab;

    fclose(file);

    return tokenizer;
}

void tokenizer_free(Tokenizer *tokenizer) {
    table_free(tokenizer->token_merge_table);
    pqueue_free(tokenizer->pqueue);
    vocab_free(tokenizer->vocab, tokenizer->vocab_size);
    free(tokenizer);
}
