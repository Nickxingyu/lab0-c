#include "sort_algo.h"
#include <string.h>
#include "queue.h"

void split_queue(list_ele_t **mid_node);
void Merge(list_ele_t **result, list_ele_t *source_1, list_ele_t *source_2);
void Msort(list_ele_t **head)
{
    if (!(*head))
        return;
    if (!(*head)->next)
        return;
    list_ele_t *left_node = *head;
    list_ele_t *right_node = *head;
    split_queue(&right_node);
    Msort(&left_node);
    Msort(&right_node);
    Merge(head, left_node, right_node);
}

void split_queue(list_ele_t **mid_node)
{
    list_ele_t *pioneer = (*mid_node)->next;
    while (pioneer) {
        pioneer = pioneer->next;
        if (pioneer) {
            pioneer = pioneer->next;
            *mid_node = (*mid_node)->next;
        }
    }
    pioneer = *mid_node;
    *mid_node = pioneer->next;
    pioneer->next = NULL;
}

void Merge(list_ele_t **result, list_ele_t *source_1, list_ele_t *source_2)
{
    list_ele_t *head = NULL;
    list_ele_t *tail = NULL;
    while (source_1 && source_2) {
        if (strcasecmp(source_1->value, source_2->value) > 0) {
            /*
             *source_2->value is smaller than or equal to source_1->value
             */
            if (!head) {
                head = tail = source_2;
            } else {
                tail->next = source_2;
                tail = source_2;
            }
            source_2 = source_2->next;
        } else {
            /*
             *source_1->value is smaller than source_2->value
             */
            if (!head) {
                head = tail = source_1;
            } else {
                tail->next = source_1;
                tail = source_1;
            }
            source_1 = source_1->next;
        }
    }
    if (source_1)
        tail->next = source_1;  // Join the remaining queue
    if (source_2)
        tail->next = source_2;  // Join the remaining queue
    *result = head;
}