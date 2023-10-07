#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>

struct node {
    struct node * next;
    void        * value;
};

struct linked_list {
    struct node * head;
};

typedef struct node        node;
typedef struct linked_list linked_list;

linked_list * linked_list_create(void);

bool linked_list_is_empty(linked_list * self);

#endif // _LINKED_LIST_H_
