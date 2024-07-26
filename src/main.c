#include <glib.h>   // open
#include <stdio.h>  // printf
#include <stdlib.h> // free

#include "basic_tokenizer.h"
#include "io.h"
#include "tokenizer_ops.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *filepath = argv[1];
        size_t filesize = get_filesize(filepath);

        char *text = read_filepath(filepath, filesize);
        Tokenizer *tokenizer = tokenizer_train(text, VOCAB_SIZE);
        GList *encoded_ids = tokenizer_encode(text, tokenizer);
        const char *decoded_text = tokenizer_decode(encoded_ids, tokenizer);

        if (strcmp(text, decoded_text) != 0) {
            perror("Original text and decoded text equal");
        }

        free(text);
        tokenizer_free(tokenizer);

        printf("Success \n");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
