#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs/table.h"
#include "tokenizer_ops.h"
#include "basic_tokenizer.h"


int main(int argc, char* argv[]) {
    if (argc == 3) {
        char* filepath = argv[1]; 
        char* second_filepath = argv[2]; 
        size_t filesize = get_filesize(filepath);
        size_t second_filesize = get_filesize(second_filepath);
        unsigned char * buffer = (unsigned char *)malloc(filesize); 
        unsigned char * second_buffer = (unsigned char *)malloc(second_filesize); 
        if (buffer == NULL || second_buffer == NULL) { 
            perror("Failed to Allocate Memory for Buffer");
            return 0;
        }
        read_filepath(filepath, buffer, filesize);
        read_filepath(second_filepath, second_buffer, second_filesize);

        GList * ids = NULL;
        buffer_to_ids(buffer, &ids, filesize);

        GList * second_ids = NULL;
        buffer_to_ids(second_buffer, &second_ids, filesize);

        static char * vocab[VOCAB_SIZE];
        get_initial_vocab(vocab);
        TokenPairToCountTable * table = table_new();
        get_merges(&ids, 10, table, vocab);
        table_print(table);

        free(buffer);
        g_list_free_full(ids, free);
        free(second_buffer);
        g_list_free_full(second_ids, free);

        table_free(table); 
        vocab_free(vocab);
        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
