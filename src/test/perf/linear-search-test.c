#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <valgrind/callgrind.h>

#include "linear-search.h"

#include "ordering.h"
#include "result.h"

ordering item_compare(const void *item, const void *item_other) {
    const uint64_t *item_typed       = item;
    const uint64_t *item_other_typed = item_other;

    if (*item_typed == *item_other_typed) {
        return EQ;
    }

    if (*item_typed > *item_other_typed) {
        return GT;
    }

    return LT;
}

int main(__attribute__((unused)) int argc, char **argv) {
    const uint64_t items_count = strtol(argv[1], NULL, 10);
    const uint64_t item_size   = sizeof(uint64_t);
    const uint64_t item        = items_count - 1;

    uint64_t *items = malloc(items_count * item_size);

    for (uint64_t item_index = 0; item_index < items_count; item_index++) {
        items[item_index] = item_index;
    }

    CALLGRIND_START_INSTRUMENTATION;
    CALLGRIND_TOGGLE_COLLECT;

    const linear_search__item_index_result result = linear_search__find(items, items_count, &item, item_size, &item_compare);

    assert(result__is_success(result));

    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;

    free(items);
}
