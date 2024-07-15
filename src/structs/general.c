#include "general.h"
#include <stdlib.h>

long *long_new(long value) {
    long *p = malloc(sizeof(long));
    *p = value;
    return p;
}

TokenPair *token_pair_new(long first_token, long second_token) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    pair->first_token = first_token;
    pair->second_token = second_token;
    return pair;
}

TokenPairCount *token_pair_count_new(long first_token, long second_token, long count) {
    TokenPairCount *pair_count = malloc(sizeof(TokenPairCount));
    pair_count->pair.first_token = first_token;
    pair_count->pair.second_token = second_token;
    pair_count->count = count;
    return pair_count;
}
