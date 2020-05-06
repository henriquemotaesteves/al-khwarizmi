#include <stdlib.h>
#include <stdio.h>
#include <valgrind/callgrind.h>

#include "linear-search.h"

ordering long_int_compare(const void *a, const void *b) {
    const long int *a_as_long_int = (const long int *)a;
    const long int *b_as_long_int = (const long int *)b;

    if (*a_as_long_int == *b_as_long_int) {
        return EQ;
    }

    if (*a_as_long_int > *b_as_long_int) {
        return GT;
    }

    return LT;
}

int main(int argc, char **argv) {
    long int number_of_items = strtol(argv[1], NULL, 10);
    size_t item_size = sizeof(long int);
    long int *items = malloc(item_size * number_of_items);

    for (long int i = 0; i < number_of_items; i++) {
        items[i] = i;
    }

    long int item_to_found = number_of_items - 1;
    size_t index_of_found_item;

    CALLGRIND_START_INSTRUMENTATION;
    CALLGRIND_TOGGLE_COLLECT;

    status status = linear_search(&long_int_compare, items, number_of_items, item_size, &item_to_found, &index_of_found_item);

    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;

    free(items);
}
