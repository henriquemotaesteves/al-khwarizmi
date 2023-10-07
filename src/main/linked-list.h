#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>
#include <stdint.h>

struct linked_list__node {
    struct linked_list__node * next;
    void                     * item;
};

struct linked_list {
    uint64_t                   size;
    struct linked_list__node * head;
};

typedef struct linked_list__node linked_list__node;
typedef struct linked_list       linked_list;

linked_list *linked_list__empty(void);

void linked_list__destroy(linked_list **list);

void * linked_list__at(const linked_list *list, uint64_t item_index);

void linked_list__add_at_start(linked_list *list, void *item);

void linked_list__add_at_end(linked_list *list, void *item);

bool linked_list__is_empty(const linked_list *list);

uint64_t linked_list__size(const linked_list *list);

#endif // _LINKED_LIST_H_
