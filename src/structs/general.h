#ifndef GENERAL_H 
#define GENERAL_H

typedef struct {
    long first_token;
    long second_token;
} TokenPair;

typedef struct {
    TokenPair pair;
    long count;
} TokenPairCount;

long* long_new(long value);

void token_pair_free(TokenPair *pair);

void value_free(long * value);

TokenPair* token_pair_new(long first_token, long second_token);
TokenPairCount * token_pair_count_new(long first_token, long second_token, long count);

#endif // GENERAL_H!
