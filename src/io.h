#ifndef IO_H 

#include <stddef.h>
#include <glib.h>

size_t get_filesize(char * filepath);

void read_filepath(char * filepath, unsigned char* buffer, size_t filesize);

void print_bytes_in_buffer(unsigned char* buffer, size_t filesize);

void print_token_pair_counts(GHashTable* token_pair_counts);

#endif
