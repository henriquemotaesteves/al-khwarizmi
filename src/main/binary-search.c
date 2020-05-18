#include "binary-search.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

status binary_search__find(
    const void *           items,
    const size_t           items_count,
    const void *           item,
    const size_t           item_size,
    const ordering_compare item_compare,
    size_t *               item_index
) {
    if (items == NULL) {
        return ITEMS_INVALID_ERROR;
    }

    if (item == NULL) {
        return ITEM_INVALID_ERROR;
    }

    if (item_size == 0) {
        return ITEM_SIZE_INVALID_ERROR;
    }

    if (item_compare == NULL) {
        return ITEM_COMPARE_INVALID_ERROR;
    }

    if (item_index == NULL) {
        return ITEM_INDEX_INVALID_ERROR;
    }

    if (items_count == 0) {
        return ITEM_NOT_FOUND_ERROR;
    }

    const uint8_t *items_octets = (const uint8_t *)items;

    size_t item_index_min = 0;
    size_t item_index_max = items_count - 1;

    while (item_index_min <= item_index_max) {
        const size_t item_index_mid = item_index_min + ((item_index_max - item_index_min) / 2);

        const void *item_mid = items_octets + item_size * item_index_mid;

        const ordering ordering = item_compare(item, item_mid);

        if (ordering == EQ) {
            *item_index = item_index_mid;

            return SUCCESS;
        }

        if (ordering == GT) {
            item_index_min = item_index_mid + 1;
        }

        if (ordering == LT) {
            item_index_max = item_index_mid - 1;
        }
    }

    return ITEM_NOT_FOUND_ERROR;
}
