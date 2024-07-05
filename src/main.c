#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <glib.h> // open 

#include "io.h"
#include "structs/table.h"
#include "tokenizer_ops.h"
#include "basic_tokenizer.h"


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

        static char * vocab[VOCAB_SIZE];
        get_initial_vocab(vocab);
        TokenPairToIntTable * table = table_new();
        get_merges(&ids, 10, table, vocab);
        table_print(table);

        free(buffer);
        free(ids);

        table_free(table); 
        vocab_free(vocab);
        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
