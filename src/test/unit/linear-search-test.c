#include "greatest.h"

#include "linear-search.h"

static const int    items[]         = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static const size_t number_of_items = 10;
static const size_t item_size       = sizeof(int);
static const int    item_to_found   = 3;

ordering int_compare(const void *a, const void *b) {
    const int *a_as_int = (const int *)a;
    const int *b_as_int = (const int *)b;

    if (*a_as_int == *b_as_int) {
        return EQ;
    }

    if (*a_as_int > *b_as_int) {
        return GT;
    }

    return LT;
}

TEST linear_search__if_compare_is_null__returns_error(void) {
    size_t index_of_found_item;

    status status = linear_search(NULL, items, number_of_items, 0, &item_to_found, &index_of_found_item);

    ASSERT_EQ(COMPARE_IS_NULL, status);
    PASS();
}

TEST linear_search__if_items_is_null__returns_error(void) {
    size_t index_of_found_item;

    status status = linear_search(&int_compare, NULL, number_of_items, item_size, &item_to_found, &index_of_found_item);

    ASSERT_EQ(ITEM_IS_NULL, status);
    PASS();
}

TEST linear_search__if_item_size_is_zero__returns_error(void) {
    size_t index_of_found_item;

    status status = linear_search(&int_compare, items, number_of_items, 0, &item_to_found, &index_of_found_item);

    ASSERT_EQ(ITEM_SIZE_IS_INVALID, status);
    PASS();
}

TEST linear_search__if_item_to_found_is_null__returns_error(void) {
    size_t index_of_found_item;

    status status = linear_search(&int_compare, items, number_of_items, item_size, NULL, &index_of_found_item);

    ASSERT_EQ(ITEM_TO_FOUND_IS_NULL, status);
    PASS();
}

TEST linear_search__if_index_of_found_item_is_null__returns_error(void) {
    int items[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t number_of_items = 10;
    size_t item_size = sizeof(int);
    int item_to_found = 3;

    status status = linear_search(&int_compare, items, number_of_items, item_size, &item_to_found, NULL);

    ASSERT_EQ(INDEX_OF_FOUND_ITEM_IS_NULL, status);
    PASS();
}

TEST linear_search__if_number_of_items_is_zero__returns_error(void) {
    size_t index_of_found_item;

    status status = linear_search(&int_compare, items, 0, item_size, &item_to_found, &index_of_found_item);

    ASSERT_EQ(ITEM_NOT_FOUND, status);
    PASS();
}

TEST linear_search__if_item_found__returns_index_of_found_item(void) {
    for (int i = 0; i < number_of_items; i++) {
        size_t index_of_found_item;

        status status = linear_search(&int_compare, items, number_of_items, item_size, &items[i], &index_of_found_item);

        ASSERT_EQ(SUCCESS, status);
        ASSERT_EQ(i, index_of_found_item);
    }

    PASS();
}

TEST linear_search__if_item_not_found__returns_error(void) {
    int item_to_found = -1;
    size_t index_of_found_item;

    status status = linear_search(&int_compare, items, number_of_items, item_size, &item_to_found, &index_of_found_item);

    ASSERT_EQ(ITEM_NOT_FOUND, status);
    PASS();
}

SUITE(linear_search_suite) {
    RUN_TEST(linear_search__if_compare_is_null__returns_error);
    RUN_TEST(linear_search__if_items_is_null__returns_error);
    RUN_TEST(linear_search__if_item_size_is_zero__returns_error);
    RUN_TEST(linear_search__if_item_to_found_is_null__returns_error);
    RUN_TEST(linear_search__if_index_of_found_item_is_null__returns_error);
    RUN_TEST(linear_search__if_number_of_items_is_zero__returns_error);
    RUN_TEST(linear_search__if_item_found__returns_index_of_found_item);
    RUN_TEST(linear_search__if_item_not_found__returns_error);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linear_search_suite);

    GREATEST_MAIN_END();
}
