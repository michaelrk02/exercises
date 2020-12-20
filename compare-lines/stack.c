/*
    stack.c: implementasi struktur data stack
*/

#include <stdlib.h>

#include "stdinc.h"

#include "begin_code.h"

void s_init(stack_t *s, void (*dealloc)(void *)) {
    s->top = NULL;
    s->dealloc = dealloc;
    if (s->dealloc == NULL) {
        s->dealloc = free;
    }
}

bool s_push(stack_t *s, linedata_t *data) {
    node_t *node;
    bool success = false;

    if ((node = (node_t *)malloc(sizeof(node_t))) != NULL) {
        node->data = data;
        node->next = s->top;
        s->top = node;
        success = true;
    } else {
        ERROR("out of memory");
    }

    return success;
}

linedata_t *s_top(const stack_t *s) {
    if (s->top != NULL) {
        return s->top->data;
    }
    return NULL;
}

void s_pop(stack_t *s, bool destroy) {
    if (s->top != NULL) {
        node_t *top = s->top;

        s->top = top->next;
        if (destroy && (top->data != NULL)) {
            s->dealloc(top->data);
        }
        free(top);
    }
}

#include "end_code.h"

