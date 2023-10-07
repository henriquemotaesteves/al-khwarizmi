#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "linked-list.h"

#include "result.h"

result(linked_list__node, linked_list__node *, linked_list__error)

linked_list__node_result linked_list__node_at(const linked_list *list, const uint64_t item_index) {
    linked_list__node *node_current = list->head;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        return linked_list__node_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
    }

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return linked_list__node_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
        }

        node_current = node_current->next;
    }

    return linked_list__node_result__success(node_current);
}

linked_list__list_result linked_list__empty(void) {
    linked_list *list = malloc(sizeof(linked_list));

    list->size = 0;
    list->head = NULL;

    return linked_list__list_result__success(list);
}

linked_list__list_result linked_list__destroy(linked_list **list) {
    if (list == NULL || *list == NULL) {
        return linked_list__list_result__failure(LIST_INVALID);
    }

    linked_list__clear(*list);

    free(*list);

    *list = NULL;

    return linked_list__list_result__success(NULL);
}

linked_list__size_result linked_list__clear(linked_list *list) {
    if (list == NULL) {
        return linked_list__size_result__failure(LIST_INVALID);
    }

    linked_list__node *node_current = list->head;

    uint64_t item_count = 0;

    while (node_current != NULL) {
        linked_list__node *node_next = node_current->next;

        node_current->item = NULL;
        node_current->next = NULL;

        free(node_current);

        node_current = node_next;

        item_count++;
    }

    list->size = 0;
    list->head = NULL;

    return linked_list__size_result__success(item_count);
}

linked_list__item_result linked_list__at(const linked_list *list, const uint64_t item_index) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    const linked_list__node *node_current = list->head;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        return linked_list__item_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
    }

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return linked_list__item_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
        }

        node_current = node_current->next;
    }

    return linked_list__item_result__success(node_current->item);
}

linked_list__item_index_result linked_list__index_of(const linked_list *list, const void *item, linked_list__item__equals item_equals) {
    if (list == NULL) {
        return linked_list__item_index_result__failure(LIST_INVALID);
    }

    if (item_equals == NULL) {
        return linked_list__item_index_result__failure(ITEM_EQUALS_INVALID);
    }

    const linked_list__node *node_current = list->head;

    uint64_t item_index = 0;

    while (node_current != NULL) {
        if (item_equals(node_current->item, item)) {
            break;
        }

        node_current = node_current->next;

        item_index++;
    }

    if (item_index == list->size) {
        return linked_list__item_index_result__failure(ITEM_NOT_FOUND);
    }

    return linked_list__item_index_result__success(item_index);
}

linked_list__item_result linked_list__insert_at(linked_list *list, const uint64_t item_index, void *item) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    if (item == NULL) {
        return linked_list__item_result__failure(ITEM_INVALID);
    }

    if (item_index == 0) {
        return linked_list__insert_at_start(list, item);
    }

    const linked_list__size_result size_result = linked_list__size(list);

    if (result__value(size_result) == item_index) {
        return linked_list__insert_at_end(list, item);
    }

    const linked_list__node_result result = linked_list__node_at(list, item_index - 1);

    if (result__is_failure(result)) {
        return linked_list__item_result__failure(result__error(result));
    }

    linked_list__node * node_previous = result__value(result);
    linked_list__node * node_current  = malloc(sizeof(linked_list__node));

    node_current->item = item;
    node_current->next = node_previous->next;

    node_previous->next = node_current;

    list->size++;

    return linked_list__item_result__success(item);
}

linked_list__item_result linked_list__insert_at_start(linked_list *list, void *item) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    if (item == NULL) {
        return linked_list__item_result__failure(ITEM_INVALID);
    }

    linked_list__node *node_head = malloc(sizeof(linked_list__node));

    node_head->item = item;
    node_head->next = list->head;

    list->head = node_head;
    list->size = list->size + 1;

    return linked_list__item_result__success(item);
}

linked_list__item_result linked_list__insert_at_end(linked_list *list, void *item) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    if (item == NULL) {
        return linked_list__item_result__failure(ITEM_INVALID);
    }

    linked_list__node *node_tail = malloc(sizeof(linked_list__node));

    node_tail->item = item;
    node_tail->next = NULL;

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        list->head = node_tail;
        list->size = 1;

        return linked_list__item_result__success(item);
    }

    linked_list__node *node_current = list->head;

    while (node_current->next != NULL) {
        node_current = node_current->next;
    }

    node_current->next = node_tail;

    list->size = list->size + 1;

    return linked_list__item_result__success(item);
}

linked_list__item_result linked_list__remove(linked_list *list, const void *item, const linked_list__item__equals item_equals) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    if (item_equals == NULL) {
        return linked_list__item_result__failure(ITEM_EQUALS_INVALID);
    }

    const linked_list__node *node_current = list->head;

    uint64_t item_index = 0;

    while (node_current != NULL) {
        if (item_equals(node_current->item, item)) {
            break;
        }

        node_current = node_current->next;

        item_index++;
    }

    if (item_index == list->size) {
        return linked_list__item_result__failure(ITEM_NOT_FOUND);
    }

    return linked_list__remove_at(list, item_index);
}

linked_list__item_result linked_list__remove_at(linked_list *list, const uint64_t item_index) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    if (item_index == 0) {
        return linked_list__remove_at_start(list);
    }

    const linked_list__node_result previous_node_result = linked_list__node_at(list, item_index - 1);

    if (result__is_failure(previous_node_result)) {
        const linked_list__error error = result__error(previous_node_result);

        return linked_list__item_result__failure(error);
    }

    linked_list__node *previous_node = result__value(previous_node_result);
    linked_list__node *current_node  = previous_node->next;

    if (current_node == NULL) {
        return linked_list__item_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
    }

    previous_node->next = current_node->next;
    list->size          = list->size - 1;

    void *item = current_node->item;

    current_node->item = NULL;
    current_node->next = NULL;

    free(current_node);

    return linked_list__item_result__success(item);
}

linked_list__item_result linked_list__remove_at_start(linked_list *list) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    if (result__value(is_empty)) {
        return linked_list__item_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
    }

    linked_list__node *node_head = list->head;
    linked_list__node *node_next = list->head->next;

    list->head = node_next;
    list->size = list->size - 1;

    void *item = node_head->item;

    node_head->item = NULL;
    node_head->next = NULL;

    free(node_head);

    return linked_list__item_result__success(item);
}

linked_list__item_result linked_list__remove_at_end(linked_list *list) {
    if (list == NULL) {
        return linked_list__item_result__failure(LIST_INVALID);
    }

    const linked_list__bool_result is_empty_result = linked_list__is_empty(list);

    if (result__value(is_empty_result)) {
        return linked_list__item_result__failure(ITEM_INDEX_OUT_OF_BOUNDS);
    }

    const linked_list__size_result size_result = linked_list__size(list);

    if (result__is_failure(size_result)) {
        return linked_list__item_result__failure(result__error(size_result));
    }

    const uint64_t size = result__value(size_result);

    if (size == 1) {
        return linked_list__remove_at_start(list);
    }

    const linked_list__node_result node_previous_result = linked_list__node_at(list, size - 2);

    if (result__is_failure(node_previous_result)) {
        return linked_list__item_result__failure(result__error(node_previous_result));
    }

    linked_list__node *node_previous = result__value(node_previous_result);
    linked_list__node *node_tail     = node_previous->next;

    node_previous->next = NULL;
    list->size          = list->size - 1;

    void *item = node_tail->item;

    node_tail->item = NULL;
    node_tail->next = NULL;

    free(node_tail);

    return linked_list__item_result__success(item);
}

linked_list__bool_result linked_list__contains(const linked_list *list, const void *item, linked_list__item__equals item_equals) {
    if (list == NULL) {
        return linked_list__bool_result__failure(LIST_INVALID);
    }

    if (item_equals == NULL) {
        return linked_list__bool_result__failure(ITEM_EQUALS_INVALID);
    }

    const linked_list__node *node_current = list->head;

    while (node_current != NULL) {
        if (item_equals(node_current->item, item)) {
            return linked_list__bool_result__success(true);
        }

        node_current = node_current->next;
    }

    return linked_list__bool_result__success(false);
}

linked_list__bool_result linked_list__is_empty(const linked_list *list) {
    if (list == NULL) {
        return linked_list__bool_result__failure(LIST_INVALID);
    }

    const bool is_empty = list->head == NULL;

    return linked_list__bool_result__success(is_empty);
}

linked_list__size_result linked_list__size(const linked_list *list) {
    if (list == NULL) {
        return linked_list__size_result__failure(LIST_INVALID);
    }

    return linked_list__size_result__success(list->size);
}
