#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"
#include "basic_tokenizer.h"


int main(int argc, char* argv[]) {
    if (argc == 2) {
        char* filepath = argv[1]; 
        size_t filesize = get_filesize(filepath);
        char * buffer = (char *)malloc(filesize+1); 
        if (buffer == NULL) { 
            perror("Failed to Allocate Memory for Buffer");
            return 0;
        }
        read_filepath(filepath, buffer, filesize);

        GList * ids = NULL;
        buffer_to_ids(buffer, &ids, filesize);

        char ** vocab = malloc(VOCAB_SIZE * sizeof(char *));
        get_initial_vocab(vocab);
        TokenPairToCountTable * table = table_new();
        TokenPairValuePriorityQueue * pqueue = pqueue_new();
        get_merges(&ids, table, pqueue, vocab, 257);

        free(buffer);
        g_list_free_full(ids, free);

        table_free(table); 
        pqueue_free(pqueue); 
        vocab_free(vocab, VOCAB_SIZE);
        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
