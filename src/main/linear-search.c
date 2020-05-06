#include "linear-search.h"

#include "ordering.h"

#include <stddef.h>
#include <stdint.h>

linear_search__item_index_result linear_search__find(
    const void             *items,
    const uint64_t         items_count,
    const void             *item,
    const uint64_t         item_size,
    const ordering_compare item_compare
) {
    if (item_compare == NULL) {
        return linear_search__item_index_result__failure(ITEM_COMPARE_INVALID);
    }

    if (items == NULL) {
        return linear_search__item_index_result__failure(ITEMS_INVALID);
    }

    if (item_size == 0) {
        return linear_search__item_index_result__failure(ITEM_SIZE_INVALID);
    }

    if (item == NULL) {
        return linear_search__item_index_result__failure(ITEM_INVALID);
    }

    if (items_count == 0) {
        return linear_search__item_index_result__failure(ITEM_NOT_FOUND);
    }

    const uint8_t *items_octets = items;

    for (uint64_t i = 0; i < items_count; i++) {
        const void *item_current = items_octets + (item_size * i);

        if (item_compare(item, item_current) == EQ) {
            return linear_search__item_index_result__success(i);
        }
    }

    return linear_search__item_index_result__failure(ITEM_NOT_FOUND);
}
