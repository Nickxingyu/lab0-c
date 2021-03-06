#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "sort_algo.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return 0;
    };
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        while (q->head) {
            list_ele_t *temp = q->head;
            q->head = q->head->next;
            free(temp->value);
            free(temp);
        }
        free(q);
    }
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return 0;
    }
    int len = strlen(s);
    char *c = (char *) malloc((len + 1) * sizeof(char));
    if (!c) {
        free(newh);
        return 0;
    }
    strncpy(c, s, len + 1);
    newh->value = c;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->size) {
        q->tail = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return 0;
    }
    int len = strlen(s);
    char *c = (char *) malloc((len + 1) * sizeof(char));
    if (!c) {
        free(newt);
        return 0;
    }
    strncpy(c, s, len + 1);
    newt->value = c;
    newt->next = NULL;
    if (!q->size) {
        q->head = newt;
    } else {
        q->tail->next = newt;
    }
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->size)
        return false;
    list_ele_t *target = q->head;
    int len = strlen(target->value) + 1;
    if (!sp)
        return 0;
    if (len > bufsize)
        len = bufsize - 1;
    strncpy(sp, target->value, len);
    sp[bufsize - 1] = 0;
    q->head = q->head->next;
    free(target->value);
    free(target);
    q->size--;
    if (!q->size)
        q->tail = NULL;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q) {
        if (q->size > 1) {
            list_ele_t *f = q->head;
            list_ele_t *s = f->next;
            list_ele_t *t = s->next;
            f->next = NULL;
            s->next = f;
            while (t) {
                f = s;
                s = t;
                t = t->next;
                s->next = f;
            }
            t = q->head;
            q->head = q->tail;
            q->tail = t;
        }
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

void q_sort(queue_t *q)
{
    if (!q || q->size <= 1)
        return;
    Msort(&(q->head));

    /* Sort elements of queue and adjust q->head.
     * Because q->tail is at the original location, following code
     * adjust q->tail to the correct location.
     */
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}