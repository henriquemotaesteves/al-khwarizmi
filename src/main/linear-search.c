#include "linear-search.h"

#include <stddef.h>
#include <stdint.h>

status linear_search(const ordering_compare compare, const void *items, const size_t number_of_items, const size_t item_size, const void *item_to_found, size_t *index_of_found_item) {
    if (compare == NULL) {
        return COMPARE_IS_NULL;
    }

    if (items == NULL) {
        return ITEM_IS_NULL;
    }

    if (item_size == 0) {
        return ITEM_SIZE_IS_INVALID;
    }

    if (item_to_found == NULL) {
        return ITEM_TO_FOUND_IS_NULL;
    }

    if (index_of_found_item == NULL) {
        return INDEX_OF_FOUND_ITEM_IS_NULL;
    }

    if (number_of_items == 0) {
        return ITEM_NOT_FOUND;
    }

    const uint8_t *items_as_bytes = (const uint8_t *)items;

    for (size_t i = 0; i < number_of_items; i++) {
        const void *item = items_as_bytes + item_size * i;

        if (compare(item, item_to_found) == EQ) {
            *index_of_found_item = i;

            return SUCCESS;
        }
    }

    return ITEM_NOT_FOUND;
}
