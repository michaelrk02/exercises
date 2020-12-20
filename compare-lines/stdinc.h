/* stdinc.h: standard include file */

#ifndef _STDINC_H /* supaya stdinc.h hanya ter-include sekali saja */
#define _STDINC_H

#ifndef __cplusplus
typedef int bool; /* definisikan tipe boolean jika dicompile menggunakan bahasa C */
#define true 1
#define false 0
#endif

bool check_extension(const char *name1, const char *name2);

typedef struct {
    int number;
    char contents[512];
} linedata_t;

struct _node_t {
    linedata_t *data;
    struct _node_t *next;
};

typedef struct _node_t node_t;

typedef struct {
    node_t *head;
    node_t *tail;
    void (*dealloc)(void *);
} queue_t;

void q_init(queue_t *q, void (*dealloc)(void *));
bool q_enqueue(queue_t *q, linedata_t *data);
linedata_t *q_head(const queue_t *q);
void q_print(queue_t *q);
void q_dequeue(queue_t *q, bool destroy);

typedef struct {
    node_t *top;
    void (*dealloc)(void *);
} stack_t;

void s_init(stack_t *s, void (*dealloc)(void *));
bool s_push(stack_t *s, linedata_t *data);
linedata_t *s_top(const stack_t *s);
void s_pop(stack_t *s, bool destroy);

#endif
