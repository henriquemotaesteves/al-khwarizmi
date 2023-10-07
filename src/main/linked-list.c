#include "linked-list.h"

#include <stdlib.h>
#include <stdio.h>

status linked_list_at(const linked_list *list, const uint64_t item_index, linked_list__node **node) {
    linked_list__node * node_current = list->head;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        return ITEM_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return ITEM_INDEX_OUT_OF_BOUNDS_ERROR;
        }

        node_current = node_current->next;
    }

    *node = node_current;

    return SUCCESS;
}

linked_list_result linked_list__empty(void) {
    linked_list *list = malloc(sizeof(linked_list));

    list->size = 0;
    list->head = NULL;

    return result__success(linked_list_result, list);
}

linked_list_result linked_list__destroy(linked_list **list) {
    linked_list__node * node_current = (*list)->head;

    while (node_current != NULL) {
        linked_list__node * node_next = node_current->next;

        node_current->item = NULL;
        node_current->next = NULL;

        free(node_current);

        node_current = node_next;
    }

    (*list)->size = 0;
    (*list)->head = NULL;

    free(*list);

    *list = NULL;

    return result__success(linked_list_result, NULL);
}

linked_list__item_result linked_list__at(const linked_list *list, const uint64_t item_index) {
    const linked_list__node * node_current = list->head;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        return result__failure(linked_list__item_result, ITEM_INDEX_OUT_OF_BOUNDS_ERROR);
    }

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return result__failure(linked_list__item_result, ITEM_INDEX_OUT_OF_BOUNDS_ERROR);
        }

        node_current = node_current->next;
    }

    return result__success(linked_list__item_result, node_current->item);
}

linked_list__item_result linked_list__insert_at(linked_list *list, const uint64_t item_index, void *item) {
    if (item_index == 0) {
        return linked_list__insert_at_start(list, item);
    }

    const linked_list__size_result size_result = linked_list__size(list);

    if (result__value(size_result) == item_index) {
        return linked_list__insert_at_end(list, item);
    }

    linked_list__node * node_previous = NULL;

    const status status = linked_list_at(list, item_index - 1, &node_previous);

    if (status != SUCCESS) {
        return result__failure(linked_list__item_result, status);
    }

    linked_list__node * node_current = malloc(sizeof(linked_list__node));

    node_current->item = item;
    node_current->next = node_previous->next;

    node_previous->next = node_current;

    list->size++;

    return result__success(linked_list__item_result, item);
}

linked_list__item_result linked_list__insert_at_start(linked_list *list, void *item) {
    if (list == NULL) {
        return result__failure(linked_list__item_result, LIST_INVALID_ERROR);
    }

    if (item == NULL) {
        return result__failure(linked_list__item_result, ITEM_INVALID_ERROR);
    }

    linked_list__node * node_head = malloc(sizeof(linked_list__node));

    node_head->item = item;
    node_head->next = list->head;

    list->head = node_head;
    list->size = list->size + 1;

    return result__success(linked_list__item_result, item);
}

linked_list__item_result linked_list__insert_at_end(linked_list *list, void *item) {
    if (list == NULL) {
        return result__failure(linked_list__item_result, LIST_INVALID_ERROR);
    }

    if (item == NULL) {
        return result__failure(linked_list__item_result, ITEM_INVALID_ERROR);
    }

    linked_list__node * node_tail = malloc(sizeof(linked_list__node));

    node_tail->item = item;
    node_tail->next = NULL;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        list->head = node_tail;
        list->size = 1;

        return result__success(linked_list__item_result, item);
    }

    linked_list__node * node_current = list->head;

    while (node_current->next != NULL) {
        node_current = node_current->next;
    }

    node_current->next = node_tail;

    list->size = list->size + 1;

    return result__success(linked_list__item_result, item);
}

linked_list__bool_result linked_list__is_empty(const linked_list *list) {
    bool is_empty = list->head == NULL;

    return result__success(linked_list__bool_result, is_empty);
}

linked_list__size_result linked_list__size(const linked_list *list) {
    return result__success(linked_list__size_result, list->size);
}
