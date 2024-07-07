#include <stdlib.h>
#include "general.h"

TokenPair *token_pair_new(long first_token, long second_token) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    pair->first_token = first_token;
    pair->second_token = second_token;
    return pair;
}

long *long_new(long value) {
    long *p = malloc(sizeof(long));
    *p = value;
    return p;
}
