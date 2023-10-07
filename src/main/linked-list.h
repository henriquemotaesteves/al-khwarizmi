#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>
#include <stdint.h>

struct node {
    struct node *next;
    void        *item;
};

struct linked_list {
    uint64_t     size;
    struct node *head;
};

typedef struct node        node;
typedef struct linked_list linked_list;

linked_list *linked_list_create(void);

void linked_list_destroy(linked_list **self);

void *linked_list_get(linked_list *self, uint64_t item_index);

void linked_list_append(linked_list *self, void *item);

void linked_list_prepend(linked_list *self, void *item);

bool linked_list_is_empty(linked_list *self);

uint64_t linked_list_size(linked_list *self);

#endif // _LINKED_LIST_H_
