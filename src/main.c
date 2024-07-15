#include <glib.h>   // open
#include <stdio.h>  // printf
#include <stdlib.h> // free

#include "basic_tokenizer.h"
#include "io.h"
#include "structs/pqueue.h"
#include "structs/table.h"
#include "tokenizer_ops.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *filepath = argv[1];
        size_t filesize = get_filesize(filepath);

        char *buffer = read_filepath(filepath, filesize);

        GList *ids = buffer_to_ids(buffer, filesize);

        char **vocab = vocab_init(VOCAB_SIZE);
        TokenPairToCountTable *table = table_new();
        TokenPairValuePriorityQueue *pqueue = pqueue_new();
        get_merges(&ids, table, pqueue, vocab, VOCAB_SIZE);

        print_ids(ids);

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
