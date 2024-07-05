#include <stdio.h>
#include "basic_tokenizer.h"

void get_merges(GList ** ids, int n_merges, TokenPairToIntTable * token_merge_table, char * vocab[VOCAB_SIZE]) {
    int n_tokens = 256;
    for (int i = n_tokens; i < n_tokens + n_merges; i++) {
        TokenPairToIntTable * token_pair_counts = table_new();
        get_stats(*ids, token_pair_counts);

        TokenPairCount * max_token_pair_count = malloc(sizeof(TokenPairCount));  
        get_max_token_pair_count(token_pair_counts, max_token_pair_count);

        GList * new_ids = NULL;
        merge(*ids, &new_ids, max_token_pair_count->pair, i);
        g_list_free_full(*ids, free);

        **ids = *new_ids;
        free(new_ids);

        table_insert_or_update(token_merge_table, &max_token_pair_count->pair, i);
        TokenPair max_pair = max_token_pair_count->pair;
        vocab[i] = (char *) malloc((strlen(vocab[max_pair.first_token]) + strlen(vocab[max_pair.second_token] + 1) * sizeof(char)));

        if (vocab[i] == NULL) {
            perror("Error allocating memory to add to vocab");
            exit(EXIT_FAILURE);
        }

        strcpy(vocab[i], vocab[max_pair.first_token]);
        strcat(vocab[i], vocab[max_pair.second_token]);

        table_free(token_pair_counts); 
    }
}