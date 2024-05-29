#include <stdio.h> // printf
#include <stdlib.h> // free 
#include <sys/stat.h> // fstat 
#include <unistd.h> // read
#include <fcntl.h> // open 

#define VOCAB_SIZE 256

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

void read_filepath(char* filepath, unsigned char* buffer, size_t filesize) {
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

    fclose(file);

    return;
}

void print_bytes_in_buffer(unsigned char* buffer, size_t filesize) { 
    for (size_t i = 0; i < filesize/sizeof(char); i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void set_counts_to_zero(unsigned int **counts, int vocab_size) { 
    for (int i = 0; i < vocab_size; i++) {
        for (int j = 0; j < vocab_size; j++) { 
            counts[i][j] = 0;
        }
    }
    return;
}

void print_counts(unsigned int **counts, int vocab_size) { 
    for (int i = 0; i < vocab_size; i++) {
        for (int j = 0; j < vocab_size; j++) { 
            if (i > j && counts[i][j] > 0) {
                if (i >= vocab_size || j >= vocab_size) {
                    perror("Vocab sizes over 255 not currently supported");
                    return;
                }
                char char_i = (char) i;
                char char_j = (char) j;
                printf("%c - %c : %d\n", char_i, char_j, counts[i][j]);
            }
        }
    }
    return;
}

void get_stats(int * ids, size_t filesize, unsigned int **counts, int vocab_size) {
    set_counts_to_zero(counts, vocab_size);

    int j;
    for (size_t i = 0; i < filesize-1; i++) {
        j = i + 1;
        int i_id = ids[i];
        int j_id = ids[j];
        if (i_id >= vocab_size || j_id >= vocab_size) {
            perror("Invalid index into vocab map");
            return;
        }
        counts[i_id][j_id]++;
    }
    return;
}

void free_counts(unsigned int **counts, int upto_index) {
   for (int i = 0; i < upto_index; i++) {   
        free(counts[i]);
    }
    free(counts); 
    return;
}

void allocate_counts(unsigned int **counts, int vocab_size) {
    for (int i = 0; i < vocab_size; i++) {
        counts[i] = malloc(vocab_size * sizeof(unsigned int));
        if (counts[i] == NULL) {
            perror("Failed to allocated counts.");
            free_counts(counts, i); 
            return;
        }
    }
    return;
}

void buffer_to_ids(unsigned char * buffer, int * ids, int sequence_length) { 
    for (int i = 0; i < sequence_length; i++) {
        ids[i] = (int) buffer[i];
    }
    return;
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

        unsigned int **counts = malloc(VOCAB_SIZE * sizeof(unsigned int *));
        if (counts == NULL) {
            perror("Error allocating 2D counts array");
            return 0;
        }
        allocate_counts(counts, VOCAB_SIZE);

        int *ids = malloc(filesize * sizeof(int));
        buffer_to_ids(buffer, ids, filesize);
        get_stats(ids, filesize, counts, VOCAB_SIZE);
        print_counts(counts, VOCAB_SIZE);
        free_counts(counts, VOCAB_SIZE);

        free(buffer);
        free(ids);
        printf("Success");

    } else {
        perror("No Filepath Specified.");
    }
    return 0;
}
