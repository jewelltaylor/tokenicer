#include <stdio.h>
#include "basic_tokenizer.h"
#include "structs/general.h"
#include "structs/pqueue.h"
#include "structs/table.h"

void get_merges(GList ** ids, long n_merges, TokenPairToCountTable * token_merge_table, TokenPairValuePriorityQueue * pqueue, char * vocab[VOCAB_SIZE]) {
    long n_tokens = 256;
    for (long i = n_tokens; i < n_tokens + n_merges; i++) {
        TokenPairToCountTable * token_pair_counts = table_new();
        get_stats(*ids, token_pair_counts);

        TokenPair * max_pair = malloc(sizeof(TokenPair));  
        table_max(token_pair_counts, max_pair);

        GList * new_ids = NULL;
        merge(*ids, &new_ids, *max_pair, i);
        g_list_free_full(*ids, free);

        *ids = new_ids;

        table_insert_or_update(token_merge_table, max_pair, i);

        TokenPairCount * pair_count = malloc(sizeof(TokenPairCount));
        pair_count->pair = *max_pair;
        pair_count->count = *long_new(i);
        pqueue_insert(pqueue, pair_count);

        vocab[i] = (char *) malloc((strlen(vocab[max_pair->first_token]) + strlen(vocab[max_pair->second_token]) + 1) * sizeof(char));

        if (vocab[i] == NULL) {
            perror("Error allocating memory to add to vocab");
            exit(EXIT_FAILURE);
        }

        strcpy(vocab[i], vocab[max_pair->first_token]);
        strcat(vocab[i], vocab[max_pair->second_token]);

        table_free(token_pair_counts); 
    }
}

void encode(GList ** ids, TokenPairValuePriorityQueue * pqueue) {
    while (g_list_length(*ids) >= 2 && pqueue_length(pqueue) != 0) { 
        TokenPairToCountTable * token_pair_counts = table_new();
        get_stats(*ids, token_pair_counts);

        TokenPairCount * pair_count = pqueue_remove(pqueue);

        if (table_lookup(token_pair_counts, &pair_count->pair) != -1) {
            GList * new_ids = NULL;
            merge(*ids, &new_ids, pair_count->pair, pair_count->count);
            g_list_free_full(*ids, free);

            *ids = new_ids;
        }

        free(pair_count);
        table_free(token_pair_counts);

    }
}
