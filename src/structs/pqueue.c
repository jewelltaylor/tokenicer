#include <glib.h>

#include "pqueue.h"
#include "general.h"

struct TokenPairValuePriorityQueue {
    GQueue * pqueue;
};

gint compare_elements(gconstpointer a, gconstpointer b, gpointer _) {
    const TokenPairCount * elem_a = a;
    const TokenPairCount * elem_b = b;
    gint dif = (gint) (elem_a->count - elem_b->count);
    return dif; 
}

TokenPairValuePriorityQueue * pqueue_new() {
   TokenPairValuePriorityQueue * pqueue = malloc(sizeof(TokenPairValuePriorityQueue));
    GQueue * glib_queue = g_queue_new();
    pqueue->pqueue = glib_queue; 
    return pqueue;
}

void pqueue_insert(TokenPairValuePriorityQueue * pqueue, TokenPairCount * pair_count) {
    gpointer g_pair_count = (gpointer) pair_count; 
    g_queue_insert_sorted(pqueue->pqueue, g_pair_count, compare_elements, NULL);
}

TokenPairCount * pqueue_remove(TokenPairValuePriorityQueue * pqueue) {
    gpointer popped_element = g_queue_pop_head(pqueue->pqueue);
    return (TokenPairCount *) popped_element;
}

unsigned long pqueue_length(TokenPairValuePriorityQueue * pqueue) {
    return (unsigned long) g_queue_get_length(pqueue->pqueue);
}

void pqueue_free(TokenPairValuePriorityQueue * pqueue) {
    g_queue_free(pqueue->pqueue);
    free(pqueue);
}






