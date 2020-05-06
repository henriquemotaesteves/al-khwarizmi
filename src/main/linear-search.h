#ifndef LINEAR_SEARCH_
#define LINEAR_SEARCH_

#include <stdint.h>

#include "ordering.h"
#include "result.h"

enum linear_search__error {
    ITEMS_INVALID,
    ITEM_COMPARE_INVALID,
    ITEM_INVALID,
    ITEM_NOT_FOUND,
    ITEM_SIZE_INVALID
};

typedef enum linear_search__error linear_search__error;

result(linear_search__item_index, uint64_t, linear_search__error)

linear_search__item_index_result linear_search__find(
    const void       *items,
    uint64_t         items_count,
    const void       *item,
    uint64_t         item_size,
    ordering_compare item_compare
);

#endif // LINEAR_SEARCH_
