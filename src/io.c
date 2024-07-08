#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <unistd.h> // read
#include <fcntl.h> // open 
#include <sys/stat.h> // fstat 
#include <glib.h> // fstat 

#include "io.h"
#include "tokenizer_ops.h"

size_t get_filesize(char* filepath) { 
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Not Valid Filepath");
        return 0;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Not Valid File Descriptor");
        close(fd);
        return 0;
    }
    
    size_t filesize = (size_t) st.st_size;

    close(fd);

    return filesize;
}

void read_filepath(char* filepath, char* buffer, size_t filesize) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    size_t read_bytes = fread(buffer, sizeof(char), filesize, file) * sizeof(char); 
    if (read_bytes != filesize) { 
        perror("Number of read bytes does not equal filesize.");
        free(buffer);
        fclose(file);
        return;
    }

    buffer[filesize] = '\0';

    fclose(file);
    return;
}

void print_bytes_in_buffer(char* buffer, size_t filesize) { 
    for (size_t i = 0; i < filesize/sizeof(char); i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}


void print_ids(GList * ids) {
    for (GList * iterator = ids; iterator != NULL; iterator = iterator->next) {
        long * id = iterator->data;
        printf("%ld ", *id);
    }
    printf("Done \n");
}

void print_vocab(char * vocab[VOCAB_SIZE]) {
    for (int i = 0; i < VOCAB_SIZE; i++) {
        if (vocab[i] == NULL || vocab[i] == 0) {
           break; 
        }

        printf("vocab[%d] = %s\n", i, vocab[i]);
    }
}
