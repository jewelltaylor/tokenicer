#ifndef IO_H

#include "tokenizer_ops.h"
#include <glib.h>
#include <stddef.h>

size_t get_filesize(char *filepath);

char *read_filepath(const char *filepath, size_t filesize);

void print_ids(GList *ids);

void print_vocab(char *vocab[VOCAB_SIZE]);

#endif
