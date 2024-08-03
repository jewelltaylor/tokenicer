#include "bpe.h"
#include "io.h"
#include "data_structures/token_pair.h"
#include "data_structures/priority_queue.h"
#include "data_structures/hash_table.h"
#include "tokenizer_ops.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

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
    Tokenizer *tokenizer = malloc(sizeof(Tokenizer));
    *tokenizer = (Tokenizer){ids, token_merge_table, pqueue, vocab, vocab_size};
    return tokenizer;
}

GList *tokenizer_encode(const char *text, Tokenizer *tokenizer) {
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
    return ids;
}

char *tokenizer_decode(GList *ids, Tokenizer *tokenizer) {
    GString *str = g_string_new("");
    for (GList *iterator = ids; iterator != NULL; iterator = iterator->next) {
        long *id = iterator->data;
        g_string_append(str, tokenizer->vocab[*id]);
    }

    char *result = g_strdup(str->str);
    g_string_free(str, TRUE);
    return result;
}

void tokenizer_free(Tokenizer *tokenizer) {
    g_list_free_full(tokenizer->ids, free);
    table_free(tokenizer->token_merge_table);
    pqueue_free(tokenizer->pqueue);
    vocab_free(tokenizer->vocab, tokenizer->vocab_size);
    free(tokenizer);
}
