#include <stdlib.h>
#include <assert.h>

#include "linked-list.h"

int main(__attribute__((unused)) int argc, char **argv) {
    long int   items_count = strtol(argv[1], NULL, 10);
    size_t     item_size   = sizeof(long int);
    long int * items       = malloc(items_count * item_size);

    for (long int i = 0; i < items_count; i++) {
        items[i] = i;
    }

    linked_list * list = linked_list_create();

    for (long int i = 0; i < items_count; i++) {
        linked_list_append(list, &items[i]);
    }

    for (long int i = 0; i < items_count; i++) {
        long int * item = linked_list_get(list, i);

        assert(*item == items[i]);
    }

    linked_list_destroy(&list);

    free(items);
}
