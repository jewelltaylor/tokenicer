#ifndef GENERAL_H 
#define GENERAL_H

typedef struct {
    int first_token;
    int second_token;
} TokenPair;

typedef struct {
    TokenPair pair;
    int count;
} TokenPairCount;

int* int_new(int value);

void token_pair_free(TokenPair *pair);

void value_free(int * value);

TokenPair* token_pair_new(int first_token, int second_token);

#endif // GENERAL_H!
