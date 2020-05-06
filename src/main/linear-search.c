#include "linear-search.h"

#include <stddef.h>
#include <stdint.h>

status linear_search(
    const void *           items,
    const size_t           items_count,
    const void *           item,
    const size_t           item_size,
    const ordering_compare item_compare,
    size_t *               item_index
) {
    if (item_compare == NULL) {
        return ITEM_COMPARE_INVALID_ERROR;
    }

    if (items == NULL) {
        return ITEMS_INVALID_ERROR;
    }

    if (item_size == 0) {
        return ITEM_SIZE_INVALID_ERROR;
    }

    if (item == NULL) {
        return ITEM_INVALID_ERROR;
    }

    if (item_index == NULL) {
        return ITEM_INDEX_INVALID_ERROR;
    }

    if (items_count == 0) {
        return ITEM_NOT_FOUND_ERROR;
    }

    const uint8_t *items_octets = (const uint8_t *)items;

    for (size_t i = 0; i < items_count; i++) {
        const void *item_current = items_octets + item_size * i;

        if (item_compare(item, item_current) == EQ) {
            *item_index = i;

            return SUCCESS;
        }
    }

    return ITEM_NOT_FOUND_ERROR;
}
