#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "linked-list.h"

void linked_list___items_inserted_at_start_and_removed_at_start___no_memory_leak_detected(const uint64_t *items, const uint64_t items_count) {
    linked_list *list = result__value(linked_list__empty());

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        linked_list__insert_at_start(list, (void *)&items[item_index]);
    }

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        const uint64_t * item = result__value(linked_list__at(list, item_index));

        assert(*item == items[item_index]);
    }

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        linked_list__remove_at_start(list);
    }

    linked_list__destroy(&list);
}

void linked_list___items_inserted_at_end_and_removed_at_end___no_memory_leak_detected(const uint64_t *items, const uint64_t items_count) {
    linked_list *list = result__value(linked_list__empty());

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        linked_list__insert_at_end(list, (void *)&items[item_index]);
    }

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        const uint64_t * item = result__value(linked_list__at(list, item_index));

        assert(*item == items[item_index]);
    }

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        linked_list__remove_at_end(list);
    }

    linked_list__destroy(&list);
}

int main(__attribute__((unused)) int argc, char **argv) {
    const uint64_t items_count = strtol(argv[1], NULL, 10);
    const uint64_t item_size   = sizeof(uint64_t);

    uint64_t *items = malloc(items_count * item_size);

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        items[item_index] = item_index;
    }

    linked_list___items_inserted_at_start_and_removed_at_start___no_memory_leak_detected(items, items_count);
    linked_list___items_inserted_at_end_and_removed_at_end___no_memory_leak_detected(items, items_count);

    free(items);
}
