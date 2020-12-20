/*
    queue.c: implementasi struktur data queue
*/

#include <stdlib.h>

#include "stdinc.h"

#include "begin_code.h"

void q_init(queue_t *q, void (*dealloc)(void *)) {
    q->head = NULL;
    q->tail = NULL;
    q->dealloc = dealloc;
    if (q->dealloc == NULL) {
        q->dealloc = free;
    }
}

bool q_enqueue(queue_t *q, linedata_t *data) {
    node_t *node;
    bool success = false;

    if ((node = (node_t *)malloc(sizeof(node_t))) != NULL) {
        node->data = data;
        node->next = NULL;
        if (q->tail == NULL) {
            q->head = node;
            q->tail = node;
        } else {
            q->tail->next = node;
            q->tail = node;
        }
        success = true;
    } else {
        ERROR("out of memory");
    }

    return success;
}

linedata_t *q_head(const queue_t *q) {
    if (q->head != NULL) {
        return q->head->data;
    }
    return NULL;
}

void q_print(queue_t *q) {
    stack_t s;

    s.top = NULL;
    s.dealloc = q->dealloc;

    while (q->head != NULL) {
        linedata_t *data = q->head->data;

        q_dequeue(q, false);
        s_push(&s, data);

        printf(" %5d > %s\n", data->number, data->contents);
    }
    while (s.top != NULL) {
        q_enqueue(q, s_top(&s));
        s_pop(&s, false);
    }
}

void q_dequeue(queue_t *q, bool destroy) {
    if (q->head != NULL) {
        node_t *head = q->head;

        q->head = head->next;
        if (q->head == NULL) {
            q->tail = NULL;
        }
        if (destroy && (head->data != NULL)) {
            q->dealloc(head->data);
        }
        free(head);
    }
}

#include "end_code.h"

