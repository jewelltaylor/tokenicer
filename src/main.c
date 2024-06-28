#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs/table.h"


void buffer_to_ids(unsigned char * buffer, GList ** pids, int sequence_length) { 
    for (int i = 0; i < sequence_length; i++) {
        int * id = malloc(sizeof(int));
        *id = (int) buffer[i];
        *pids = g_list_prepend(*pids, id);
    }
    *pids = g_list_reverse(*pids);
    return;
}

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

void get_max_token_pair_count(TokenPairToIntTable * token_pair_counts, TokenPairCount * max_token_pair_count) {
    GList *keys = NULL;
    table_keys(token_pair_counts, &keys);
    GList *iter = keys; 

    TokenPair *max_pair = NULL;
    int *max_value = malloc(sizeof(int));

    while (iter != NULL) {
        TokenPair *pair = (TokenPair *)iter->data;
        int value = table_lookup(token_pair_counts, pair);

        if ((max_value == NULL) || (max_value != NULL && value > *max_value)) {
            max_pair = pair; 
            *max_value = value;
        }
        iter = iter->next;
    }
    g_list_free(keys);

    if (max_pair == NULL || max_value == NULL) {
        perror("Error getting max token pair");
        return;
    }
    TokenPair* new_max_pair = malloc(sizeof(TokenPair)); 
    int* new_max_value = malloc(sizeof(int)); 
    *new_max_pair = *max_pair;
    *new_max_value = *max_value;
    max_token_pair_count->pair = *new_max_pair;
    max_token_pair_count->count = *new_max_value;

    return;
}

void merge(GList * ids, GList ** new_pids, TokenPairCount * token_pair_count, int id) {
    TokenPair pair = token_pair_count->pair;
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

void get_merges(GList ** pids, int n_merges, TokenPairToIntTable * token_merge_table) {
    int n_tokens = 256;
    for (int i = 0; i < n_merges; i++) {
        TokenPairToIntTable * token_pair_counts = table_new();
        get_stats(*pids, token_pair_counts);

        TokenPairCount * max_token_pair_count = malloc(sizeof(TokenPairCount));  
        get_max_token_pair_count(token_pair_counts, max_token_pair_count);

        GList * new_ids = NULL;
        merge(*pids, &new_ids, max_token_pair_count, n_tokens+i);
        g_list_free_full(*pids, free);

        **pids = *new_ids;
        free(new_ids);

        table_insert_or_update(token_merge_table, &max_token_pair_count->pair, n_tokens+i);

        table_free(token_pair_counts); 
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        char* filepath = argv[1]; 
        size_t filesize = get_filesize(filepath);
        unsigned char * buffer = (unsigned char *)malloc(filesize); 
        if (buffer == NULL) { 
            perror("Failed to Allocate Memory for Buffer");
            return 0;
        }
        read_filepath(filepath, buffer, filesize);

        GList * ids = NULL;
        buffer_to_ids(buffer, &ids, filesize);

        TokenPairToIntTable * table = table_new();
        get_merges(&ids, 5, table);
        table_print(table);

        print_ids(ids);

        free(buffer);
        free(ids);

        table_free(table); 
        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
