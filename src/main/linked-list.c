#include "linked-list.h"

#include <stdlib.h>
#include <stdio.h>

linked_list * linked_list__empty(void) {
    linked_list *list = (linked_list *) malloc(sizeof(linked_list));

    list->size = 0;
    list->head = NULL;

    return list;
}

void linked_list__destroy(linked_list **list) {
    linked_list__node * node_current = (*list)->head;

    while (node_current != NULL) {
        linked_list__node * node_next = node_current->next;

        free(node_current);

        node_current = node_next;
    }

    free(*list);

    *list = NULL;
}

void * linked_list__at(const linked_list *list, const uint64_t item_index) {
    linked_list__node * node_current = list->head;

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return NULL;
        }

        node_current = node_current->next;
    }

    return node_current->item;
}

void linked_list__add_at_start(linked_list *list, void * item) {
    linked_list__node * node_next = (linked_list__node *) malloc(sizeof(linked_list__node));

    node_next->item = item;
    node_next->next = NULL;

    if (linked_list__is_empty(list)) {
        list->head = node_next;

        list->size = 1;

        return;
    }

    linked_list__node * node_current = list->head;

    while (node_current->next != NULL) {
        node_current = node_current->next;
    }

    node_current->next = node_next;

    list->size = list->size + 1;
}

void linked_list__add_at_end(linked_list *list, void * item) {
    linked_list__node * node_head = (linked_list__node *) malloc(sizeof(linked_list__node));

    node_head->item = item;
    node_head->next = list->head;
    
    list->head = node_head;
    list->size = list->size + 1;
}

bool linked_list__is_empty(const linked_list *list) {
    return list->head == NULL;
}

uint64_t linked_list__size(const linked_list *list) {
    return list->size;
}
