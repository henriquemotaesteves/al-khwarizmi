#ifndef BINARY_SEARCH_
#define BINARY_SEARCH_

#include <stdint.h>

#include "ordering.h"
#include "result.h"

enum binary_search__error {
    ITEMS_INVALID,
    ITEM_COMPARE_INVALID,
    ITEM_INVALID,
    ITEM_NOT_FOUND,
    ITEM_SIZE_INVALID
};

typedef enum binary_search__error binary_search__error;

result(binary_search__item_index, uint64_t, binary_search__error)

binary_search__item_index_result binary_search__find(
    const void       *items,
    uint64_t         items_count,
    const void       *item,
    uint64_t         item_size,
    ordering_compare item_compare
);

#endif // BINARY_SEARCH_
