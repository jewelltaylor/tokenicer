#include <glib.h>
#include <stdio.h>

#include "token_pair.h"
#include "priority_queue.h"

struct TokenPairValuePriorityQueue {
    GQueue *pqueue;
};

gint compare_elements(gconstpointer a, gconstpointer b, gpointer _) {
    const TokenPairCount *elem_a = a;
    const TokenPairCount *elem_b = b;
    gint dif = (gint)(elem_a->count - elem_b->count);
    return dif;
}

TokenPairValuePriorityQueue *pqueue_new() {
    TokenPairValuePriorityQueue *pqueue = malloc(sizeof(TokenPairValuePriorityQueue));
    GQueue *glib_queue = g_queue_new();
    pqueue->pqueue = glib_queue;
    return pqueue;
}

void pqueue_insert(TokenPairValuePriorityQueue *pqueue, TokenPairCount *pair_count) {
    g_queue_insert_sorted(pqueue->pqueue, pair_count, compare_elements, NULL);
}

void pqueue_remove(TokenPairValuePriorityQueue *pqueue) {
    TokenPairCount *pair_count = (TokenPairCount *)g_queue_pop_head(pqueue->pqueue);
    free(pair_count);
}

long pqueue_size(TokenPairValuePriorityQueue *pqueue) {
    return (long) g_queue_get_length(pqueue->pqueue);
}

const TokenPairCount *pqueue_peek(TokenPairValuePriorityQueue *pqueue) {
    gpointer popped_element = g_queue_peek_head(pqueue->pqueue);
    return (TokenPairCount *)popped_element;
}

unsigned long pqueue_length(TokenPairValuePriorityQueue *pqueue) {
    return (unsigned long)g_queue_get_length(pqueue->pqueue);
}

void pqueue_token_pair_count_save(gpointer data, gpointer user_data) {
    TokenPairCount *pair_count = (TokenPairCount *) data;
    FILE *file =  (FILE *) user_data;
    fwrite(pair_count, sizeof(TokenPairCount), 1, file);
}

void pqueue_save(TokenPairValuePriorityQueue *pqueue, FILE *file) { 
    long size = pqueue_size(pqueue);
    fwrite(&size, sizeof(long), 1, file);

    g_queue_foreach(pqueue->pqueue, (GFunc) pqueue_token_pair_count_save, file);  
}

TokenPairValuePriorityQueue *pqueue_load(FILE *file) {
    long pqueue_length;
    fread(&pqueue_length, sizeof(long), 1, file);

    TokenPairValuePriorityQueue *pqueue = pqueue_new();

    for (long i = 0; i < pqueue_length; i++) { 
        TokenPairCount *pair_count = malloc(sizeof(TokenPairCount)); 
        fread(pair_count, sizeof(TokenPairCount), 1, file); 
        pqueue_insert(pqueue, pair_count);
    }
    return pqueue;
}

void pqueue_free(TokenPairValuePriorityQueue *pqueue) {
    g_queue_free_full(pqueue->pqueue, free);
    free(pqueue);
}
