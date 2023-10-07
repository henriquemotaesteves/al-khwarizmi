#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>
#include <stdint.h>

#include "result.h"
#include "status.h"

#define LIST_INVALID_ERROR             (ERROR | 0x00000001)
#define ITEM_INVALID_ERROR             (ERROR | 0x00000002)
#define ITEM_INDEX_OUT_OF_BOUNDS_ERROR (ERROR | 0x00000003)

struct linked_list__node {
    struct linked_list__node * next;
    void                     * item;
};

struct linked_list {
    uint64_t                   size;
    struct linked_list__node * head;
    struct linked_list__node * tail;
};

typedef struct linked_list__node linked_list__node;
typedef struct linked_list       linked_list;

result(linked_list,             linked_list *, uint32_t)
result(linked_list__bool,       bool,          uint32_t)
result(linked_list__item,       void *,        uint32_t)
result(linked_list__item_index, uint64_t,      uint32_t)
result(linked_list__size,       uint64_t,      uint32_t)

linked_list_result linked_list__empty(void);

linked_list_result linked_list__destroy(linked_list **list);

linked_list__item_result linked_list__at(const linked_list *list, uint64_t item_index);

linked_list__item_result linked_list__insert_at(linked_list *list, uint64_t item_index, void *item);

linked_list__item_result linked_list__insert_at_start(linked_list *list, void *item);

linked_list__item_result linked_list__insert_at_end(linked_list *list, void *item);

linked_list__bool_result linked_list__is_empty(const linked_list *list);

linked_list__size_result linked_list__size(const linked_list *list);

#endif // _LINKED_LIST_H_
