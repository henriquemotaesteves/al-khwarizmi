#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdbool.h>
#include <stdint.h>

#include "result.h"

enum linked_list__error {
    LIST_INVALID,
    ITEM_EQUALS_INVALID,
    ITEM_INDEX_OUT_OF_BOUNDS,
    ITEM_INVALID,
    ITEM_NOT_FOUND
};

typedef enum linked_list__error linked_list__error;

struct linked_list__node {
    struct linked_list__node *next;
    void                     *item;
};

struct linked_list {
    uint64_t                 size;
    struct linked_list__node *head;
    struct linked_list__node *tail;
};

typedef struct linked_list__node linked_list__node;
typedef struct linked_list       linked_list;

typedef bool (*linked_list__item__equals)(const void *, const void *);

result(linked_list__bool,       bool,          linked_list__error)
result(linked_list__item,       void *,        linked_list__error)
result(linked_list__item_index, uint64_t,      linked_list__error)
result(linked_list__list,       linked_list *, linked_list__error)
result(linked_list__size,       uint64_t,      linked_list__error)

linked_list__list_result linked_list__empty(void);

linked_list__list_result linked_list__destroy(linked_list **list);

linked_list__size_result linked_list__clear(linked_list *list);

linked_list__item_result linked_list__at(const linked_list *list, uint64_t item_index);

linked_list__item_index_result linked_list__index_of(const linked_list *list, const void *item, linked_list__item__equals item_equals);

linked_list__item_result linked_list__insert_at(linked_list *list, uint64_t item_index, void *item);

linked_list__item_result linked_list__insert_at_start(linked_list *list, void *item);

linked_list__item_result linked_list__insert_at_end(linked_list *list, void *item);

linked_list__item_result linked_list__remove(linked_list *list, const void *item, linked_list__item__equals item_equals);

linked_list__item_result linked_list__remove_at(linked_list *list, uint64_t item_index);

linked_list__item_result linked_list__remove_at_start(linked_list *list);

linked_list__item_result linked_list__remove_at_end(linked_list *list);

linked_list__bool_result linked_list__contains(const linked_list *list, const void *item, linked_list__item__equals item_equals);

linked_list__bool_result linked_list__is_empty(const linked_list *list);

linked_list__size_result linked_list__size(const linked_list *list);

#endif // LINKED_LIST_H_
