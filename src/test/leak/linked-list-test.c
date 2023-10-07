#include <stdlib.h>
#include <assert.h>

#include "linked-list.h"

int main(__attribute__((unused)) int argc, char **argv) {
    const long int items_count = strtol(argv[1], NULL, 10);
    const size_t   item_size   = sizeof(long int);
    long int *     items       = malloc(items_count * item_size);

    for (long int i = 0; i < items_count; i++) {
        items[i] = i;
    }

    linked_list *list = result__value(linked_list__empty());

    for (long int i = 0; i < items_count; i++) {
        linked_list__insert_at_end(list, &items[i]);
    }

    for (long int i = 0; i < items_count; i++) {
        const long int * item = result__value(linked_list__at(list, i));

        assert(*item == items[i]);
    }

    linked_list__destroy(&list);

    free(items);
}
