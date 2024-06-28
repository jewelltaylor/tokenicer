#include <stdlib.h>
#include "general.h"

TokenPair *token_pair_new(int first_token, int second_token) {
    TokenPair *pair = malloc(sizeof(TokenPair));
    pair->first_token = first_token;
    pair->second_token = second_token;
    return pair;
}

int *int_new(int value) {
    int *p = malloc(sizeof(int));
    *p = value;
    return p;
}
