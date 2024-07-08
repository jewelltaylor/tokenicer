#ifndef IO_H 

#include <stddef.h>
#include <glib.h>
#include "tokenizer_ops.h"

size_t get_filesize(char * filepath);

void read_filepath(char * filepath, char* buffer, size_t filesize);

void print_bytes_in_buffer(char* buffer, size_t filesize);

void print_ids(GList * ids);

void print_vocab(char * vocab[VOCAB_SIZE]);

#endif
