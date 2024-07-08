#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"
#include "basic_tokenizer.h"


int main(int argc, char* argv[]) {
    if (argc == 3) {
        char* filepath = argv[1]; 
        char* second_filepath = argv[2]; 
        size_t filesize = get_filesize(filepath);
        size_t second_filesize = get_filesize(second_filepath);
        char * buffer = (char *)malloc(filesize+1); 
        char * second_buffer = (char *)malloc(second_filesize+1); 
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
        TokenPairValuePriorityQueue * pqueue = pqueue_new();
        get_merges(&ids, 10, table, pqueue, vocab);


        encode(&second_ids, pqueue);
        char * decoded_encoded_text = decode(second_ids, vocab);
        char * decoded_merged_text = decode(ids, vocab);
        printf("%s\n%s\n%s\n", buffer, decoded_encoded_text, decoded_merged_text);

        free(buffer);
        g_list_free_full(ids, free);
        free(second_buffer);
        g_list_free_full(second_ids, free);

        free(decoded_merged_text);
        free(decoded_encoded_text);
        table_free(table); 
        pqueue_free(pqueue); 
        vocab_free(vocab);
        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
