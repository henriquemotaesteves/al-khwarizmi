#include "greatest.h"

#include "linear-search.h"

static const int              ITEMS[]              = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static const int *            ITEMS_INVALID        = NULL;
static const size_t           ITEMS_COUNT          = 10;
static const int *            ITEM_INVALID         = NULL;
static const int              ITEM_FOUND           = 3;
static const int              ITEM_NOT_FOUND       = 10;
static const size_t           ITEM_SIZE            = sizeof(int);
static const size_t           ITEM_SIZE_INVALID    = 0;
static const ordering_compare ITEM_COMPARE_INVALID = NULL;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
static const int              ITEMS_EMPTY[0]       = { };
static const size_t           ITEMS_EMPTY_COUNT    = 0;
#pragma GCC diagnostic pop

ordering item_compare(const void *item_expected, const void *item_current) {
    const int *item_expected_int = (const int *)item_expected;
    const int *item_current_int  = (const int *)item_current;

    if (*item_expected_int == *item_current_int) {
        return EQ;
    }

    if (*item_expected_int > *item_current_int) {
        return GT;
    }

    return LT;
}

TEST linear_search__if_items_is_invalid__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS_INVALID, ITEMS_COUNT, &ITEM_FOUND, ITEM_SIZE, &item_compare, &item_index);

    ASSERT_EQ(ITEMS_INVALID_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

TEST linear_search__if_item_is_invalid__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS, ITEMS_COUNT, ITEM_INVALID, ITEM_SIZE, &item_compare, &item_index);

    ASSERT_EQ(ITEM_INVALID_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

TEST linear_search__if_item_size_is_invalid__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS, ITEMS_COUNT, &ITEM_FOUND, ITEM_SIZE_INVALID, &item_compare, &item_index);

    ASSERT_EQ(ITEM_SIZE_INVALID_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

TEST linear_search__if_item_compare_is_invalid__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS, ITEMS_COUNT, &ITEM_FOUND, ITEM_SIZE, ITEM_COMPARE_INVALID, &item_index);

    ASSERT_EQ(ITEM_COMPARE_INVALID_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

TEST linear_search__if_item_index_is_invalid__returns_error_and_does_not_assign_item_index(void) {
    size_t *item_index = NULL;

    status status = linear_search(ITEMS, ITEMS_COUNT, &ITEM_FOUND, ITEM_SIZE, &item_compare, item_index);

    ASSERT_EQ(ITEM_INDEX_INVALID_ERROR, status);
    ASSERT_EQ(NULL, item_index);
    PASS();
}

TEST linear_search__if_items_is_empty__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS_EMPTY, ITEMS_EMPTY_COUNT, &ITEM_FOUND, ITEM_SIZE, &item_compare, &item_index);

    ASSERT_EQ(ITEM_NOT_FOUND_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

TEST linear_search__if_item_is_found__returns_success_and_assigns_item_index(void) {
    for (int i = 0; i < ITEMS_COUNT; i++) {
        size_t item_index = -1;

        status status = linear_search(ITEMS, ITEMS_COUNT, &ITEMS[i], ITEM_SIZE, &item_compare, &item_index);

        ASSERT_EQ(status, SUCCESS);
        ASSERT_EQ(i, item_index);
    }

    PASS();
}

TEST linear_search__if_item_is_not_found__returns_error_and_does_not_assign_item_index(void) {
    size_t item_index = -1;

    status status = linear_search(ITEMS, ITEMS_COUNT, &ITEM_NOT_FOUND, ITEM_SIZE, &item_compare, &item_index);

    ASSERT_EQ(ITEM_NOT_FOUND_ERROR, status);
    ASSERT_EQ(-1, item_index);
    PASS();
}

SUITE(linear_search_suite) {
    RUN_TEST(linear_search__if_items_is_invalid__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_items_is_empty__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_item_is_invalid__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_item_size_is_invalid__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_item_compare_is_invalid__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_item_index_is_invalid__returns_error_and_does_not_assign_item_index);
    RUN_TEST(linear_search__if_item_is_found__returns_success_and_assigns_item_index);
    RUN_TEST(linear_search__if_item_is_not_found__returns_error_and_does_not_assign_item_index);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linear_search_suite);

    GREATEST_MAIN_END();
}
