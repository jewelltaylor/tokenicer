#include <glib.h>   // open
#include <stdio.h>  // printf
#include <stdlib.h> // free

#include "bpe.h"
#include "data_structures/hash_table.h"
#include "io.h"
#include "tokenizer_ops.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *filepath = argv[1];
        size_t filesize = get_filesize(filepath);

        char *text = read_filepath(filepath, filesize);

        Tokenizer *tokenizer = tokenizer_train(text, VOCAB_SIZE);
        GList *encoded_ids = tokenizer_encode(tokenizer, text);
        char *decoded_text = tokenizer_decode(tokenizer, encoded_ids);

        if (strcmp(text, decoded_text) != 0) {
            perror("Original text and decoded text equal");
        }

        tokenizer_free(tokenizer);
        free(text);
        g_list_free_full(encoded_ids, free);
        free(decoded_text);

        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
