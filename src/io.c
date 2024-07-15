#include <fcntl.h>    // open
#include <glib.h>     // fstat
#include <stdio.h>    // printf
#include <stdlib.h>   // free
#include <sys/stat.h> // fstat
#include <unistd.h>   // read

#include "io.h"

size_t get_filesize(char *filepath) {
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Not Valid Filepath");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Not Valid File Descriptor");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t filesize = (size_t)st.st_size;

    close(fd);

    return filesize;
}

char *read_filepath(const char *filepath, size_t filesize) {
    char *buffer = (char *)malloc(filesize + 1);
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t read_bytes = fread(buffer, sizeof(char), filesize, file) * sizeof(char);
    if (read_bytes != filesize) {
        perror("Number of read bytes does not equal filesize.");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    buffer[filesize] = '\0';

    fclose(file);
    return buffer;
}

void print_ids(GList *ids) {
    for (const GList *iterator = ids; iterator != NULL; iterator = iterator->next) {
        const long *id = iterator->data;
        printf("%ld ", *id);
    }
    printf("Done \n");
}
