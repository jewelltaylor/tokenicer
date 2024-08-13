#include <stdio.h>  // printf
#include <stdlib.h> // free

char **vocab_init(long vocab_size) {
    char **vocab = malloc(vocab_size * sizeof(char *));
    for (long i = 0; i < 256; i++) {
        vocab[i] = (char *)malloc(2 * sizeof(char));

        if (vocab[i] == NULL) {
            perror("Error allocating initial vocab");
            exit(EXIT_FAILURE);
        }

        vocab[i][0] = (char)i;
        vocab[i][1] = '\0';
    }
    return vocab;
}

void vocab_size_save(long vocab_size, FILE * file) { fwrite(&vocab_size, sizeof(long), 1, file); }
long vocab_size_load(FILE *file) { 
    long vocab_size;
    fread(&vocab_size, sizeof(long), 1, file); 
    return vocab_size;
}

void vocab_save(char **vocab, long vocab_size, FILE *file) {
    for (long i = 256; i < vocab_size; i++) { 
        int token_length = strlen(vocab[i]) + 1;
        fwrite(&token_length, sizeof(int), 1, file);
        fwrite(vocab[i], sizeof(char), token_length, file);
    }
}

char **vocab_load(FILE *file, long vocab_size) {
    char **vocab = vocab_init(vocab_size);
    for (long i = 256; i < vocab_size; i++) { 
        int token_length;
        fread(&token_length, sizeof(int), 1, file);
        vocab[i] = (char *) malloc(token_length * sizeof(char));
        fread(vocab[i], sizeof(char), token_length, file); 
    }
    return vocab;
}

void vocab_free(char **vocab, long vocab_size) {
    for (long i = 0; i < vocab_size; i++) {
        if (vocab[i] == NULL) {
            break;
        }

        free(vocab[i]);
    }
    free(vocab);
}
