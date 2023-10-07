#include "linked-list.h"

#include <stdlib.h>
#include <stdio.h>

linked_list * linked_list_create(void) {
    linked_list * self = (linked_list *) malloc(sizeof(linked_list));

    self->size = 0;
    self->head = NULL;

    return self;
}

void linked_list_destroy(linked_list ** self) {
    node * node_current = (*self)->head;

    while (node_current != NULL) {
        node * node_next = node_current->next;

        free(node_current);

        node_current = node_next;
    }

    free(*self);

    *self = NULL;
}

void * linked_list_get(linked_list * self, uint64_t item_index) {
    node * node_current = self->head;

    for (uint64_t item_current_index = 0; item_current_index < item_index; item_current_index++) {
        if (node_current->next == NULL) {
            return NULL;
        }

        node_current = node_current->next;
    }

    return node_current->item;
}

void linked_list_append(linked_list * self, void * item) {
    node * node_next = (node *) malloc(sizeof(node));
    node_next->item  = item;
    node_next->next  = NULL;

    if (linked_list_is_empty(self)) {
        self->head = node_next;

        self->size = self->size + 1;
        
        return;
    }

    node * node_current = self->head;

    while (node_current->next != NULL) {
        node_current = node_current->next;
    }

    node_current->next = node_next;

    self->size = self->size + 1;
}

void linked_list_prepend(linked_list * self, void * item) {
    node * node_head = (node *) malloc(sizeof(node));
    node_head->item  = item;
    node_head->next  = self->head;
    
    self->head = node_head;
    self->size = self->size + 1;
}

bool linked_list_is_empty(linked_list * self) {
    return self->head == NULL;
}

uint64_t linked_list_size(linked_list * self) {
    return self->size;
}
