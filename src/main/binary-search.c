#include "binary-search.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

status binary_search(const ordering_compare compare, const void *items, const size_t number_of_items, const size_t item_size, const void *item_to_found, size_t *index_of_found_item) {
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

    size_t index_of_first_item = 0;
    size_t index_of_last_item  = number_of_items - 1;

    while (true) {
        const size_t index_of_middle_item = index_of_first_item + ((index_of_last_item - index_of_first_item) / 2);

        const void *middle_item = items_as_bytes + item_size * index_of_middle_item;

        const ordering ordering = compare(middle_item, item_to_found);

        if (ordering == EQ) {
            *index_of_found_item = index_of_middle_item;

            return SUCCESS;
        }

        if (index_of_first_item == index_of_last_item) {
            break;
        }

        if (ordering == GT) {
            index_of_last_item  = index_of_middle_item - 1;
        }

        if (ordering == LT) {
            index_of_first_item = index_of_middle_item + 1;
        }
    }

    return ITEM_NOT_FOUND;
}
