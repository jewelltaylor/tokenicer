#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs.h"


void buffer_to_ids(unsigned char * buffer, int * ids, int sequence_length) { 
    for (int i = 0; i < sequence_length; i++) {
        ids[i] = (int) buffer[i];
    }
    return;
}

void get_stats(int * ids, int n_tokens, GHashTable * token_pair_counts) {
    for (int i = 0; i < n_tokens - 1; i++) { 
        TokenPair * pair = token_pair_new(ids[i], ids[i+1]);
        int * lookup = g_hash_table_lookup(token_pair_counts, pair);

        if (lookup == NULL) {
            g_hash_table_insert(token_pair_counts, pair, int_new(1));
        } else {
            int prev_val = *lookup;
            g_hash_table_replace(token_pair_counts, pair, int_new(prev_val + 1));
        }
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

        // print_bytes_in_buffer(buffer, filesize);

        int *ids = malloc(filesize * sizeof(int));
        buffer_to_ids(buffer, ids, filesize);

        GHashTable *token_pair_counts = g_hash_table_new_full(token_pair_hash, token_pair_equal, token_pair_free, value_free); 

        get_stats(ids, filesize, token_pair_counts);
        print_token_pair_counts(token_pair_counts);

        free(buffer);
        free(ids);
        g_hash_table_destroy(token_pair_counts); 
        printf("Success");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
