#include <stdlib.h>
#include <valgrind/callgrind.h>
#include <assert.h>

#include "binary-search.h"

ordering item_compare(const void *item_expected, const void *item_current) {
    const long int *item_expected_long_int = (const long int *)item_expected;
    const long int *item_current_long_int  = (const long int *)item_current;

    if (*item_expected_long_int == *item_current_long_int) {
        return EQ;
    }

    if (*item_expected_long_int > *item_current_long_int) {
        return GT;
    }

    return LT;
}

int main(__attribute__((unused)) int argc, char **argv) {
    long int   items_count = strtol(argv[1], NULL, 10);
    size_t     item_size   = sizeof(long int);
    long int * items       = malloc(items_count * item_size);
    long int   item        = items_count - 1;
    size_t     item_index  = 0;

    for (long int i = 0; i < items_count; i++) {
        items[i] = i;
    }

    CALLGRIND_START_INSTRUMENTATION;
    CALLGRIND_TOGGLE_COLLECT;

    status status = binary_search__find(
            items,
            items_count,
            &item,
            item_size,
            &item_compare,
            &item_index);

    assert(status == SUCCESS);

    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;

    free(items);
}
