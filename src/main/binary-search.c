#include "binary-search.h"

#include "ordering.h"

#include <stddef.h>
#include <stdint.h>

binary_search__item_index_result binary_search__find(
    const void             *items,
    const uint64_t         items_count,
    const void             *item,
    const uint64_t         item_size,
    const ordering_compare item_compare
) {
    if (item_compare == NULL) {
        return binary_search__item_index_result__failure(ITEM_COMPARE_INVALID);
    }

    if (items == NULL) {
        return binary_search__item_index_result__failure(ITEMS_INVALID);
    }

    if (item_size == 0) {
        return binary_search__item_index_result__failure(ITEM_SIZE_INVALID);
    }

    if (item == NULL) {
        return binary_search__item_index_result__failure(ITEM_INVALID);
    }

    if (items_count == 0) {
        return binary_search__item_index_result__failure(ITEM_NOT_FOUND);
    }

    const uint8_t *items_octets = items;

    uint64_t item_index_min = 0;
    uint64_t item_index_max = items_count - 1;

    while (item_index_min <= item_index_max) {
        const uint64_t item_index_mid = item_index_min + ((item_index_max - item_index_min) / 2);

        const void *item_mid = items_octets + (item_size * item_index_mid);

        const ordering ordering = item_compare(item, item_mid);

        if (ordering == EQ) {
            return binary_search__item_index_result__success(item_index_mid);
        }

        if (ordering == GT) {
            item_index_min = item_index_mid + 1;
        }

        if (ordering == LT) {
            item_index_max = item_index_mid - 1;
        }
    }

    return binary_search__item_index_result__failure(ITEM_NOT_FOUND);
}
