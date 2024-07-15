#include "basic_tokenizer.h"
#include "structs/general.h"
#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

void get_merges(GList **ids, TokenPairToCountTable *token_merge_table, TokenPairValuePriorityQueue *pqueue,
                char **vocab, long vocab_size) {
    for (long i = 256; i < vocab_size - 256; i++) {
        TokenPairToCountTable *token_pair_counts = table_new();
        get_stats(*ids, token_pair_counts);

        TokenPair *max_pair = malloc(sizeof(TokenPair));
        table_max(token_pair_counts, max_pair);
        table_insert_or_update(token_merge_table, max_pair, i);

        *ids = merge(*ids, *max_pair, i);

        TokenPairCount *pair_count = token_pair_count_new(max_pair->first_token, max_pair->second_token, i);
        pqueue_insert(pqueue, pair_count);

        int token_str_len = strlen(vocab[max_pair->first_token]) + strlen(vocab[max_pair->second_token]) + 1;
        vocab[i] = (char *)malloc(token_str_len * sizeof(char));
        strcpy(vocab[i], vocab[max_pair->first_token]);
        strcat(vocab[i], vocab[max_pair->second_token]);

        table_free(token_pair_counts);
    }
}

void encode(GList **ids, TokenPairValuePriorityQueue *pq) {
    while (g_list_length(*ids) >= 2 && pqueue_length(pq) != 0) {
        TokenPairToCountTable *table = table_new();
        get_stats(*ids, table);

        while (pqueue_length(pq) && table_lookup(table, &pqueue_peek(pq)->pair) == -1)
            pqueue_remove(pq);

        if (pqueue_length(pq)) {
            const TokenPairCount *head = pqueue_peek(pq);
            TokenPairCount *pair_count =
                token_pair_count_new(head->pair.first_token, head->pair.second_token, head->count);
            *ids = merge(*ids, pair_count->pair, pair_count->count);
            free(pair_count);
        }
        table_free(table);
    }
}

char *decode(GList *ids, char **vocab) {
    GString *str = g_string_new("");
    for (GList *iterator = ids; iterator != NULL; iterator = iterator->next) {
        long *id = iterator->data;
        g_string_append(str, vocab[*id]);
    }

    char *result = g_strdup(str->str);
    g_string_free(str, TRUE);
    return result;
}
