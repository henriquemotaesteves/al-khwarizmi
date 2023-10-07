#include "linked-list.h"

#include <stdlib.h>

linked_list * linked_list_create(void) {
    linked_list * self = malloc(sizeof(linked_list));

    self->head = NULL;

    return self;
}

bool linked_list_is_empty(linked_list * self) {
    return self->head == NULL;
}