#include <stddef.h>
#include <stdint.h>

#include "greatest.h"

#include "linear-search.h"

#include "ordering.h"
#include "result.h"

static const uint32_t ITEMS[]     = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static const uint32_t ITEMS_COUNT = 10;
static const uint32_t ITEM_SIZE   = sizeof(uint32_t);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
static const uint32_t ITEMS_EMPTY[0]    = { };
static const uint32_t ITEMS_EMPTY_COUNT = 0;
#pragma GCC diagnostic pop

ordering item_compare(const void *item, const void *item_other) {
    const uint32_t *item_typed       = item;
    const uint32_t *item_other_typed = item_other;

    if (*item_typed == *item_other_typed) {
        return EQ;
    }

    if (*item_typed > *item_other_typed) {
        return GT;
    }

    return LT;
}

TEST linear_search__find___items_is_invalid___result_is_failure_with_items_invalid_error(void) {
    const uint32_t item = 3;

    const linear_search__item_index_result result = linear_search__find(
        NULL,
        ITEMS_COUNT,
        &item,
        ITEM_SIZE,
        &item_compare);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEMS_INVALID, result__error(result));
    PASS();
}

TEST linear_search__find___item_is_invalid___result_is_failure_with_item_invalid_error(void) {
    const linear_search__item_index_result result = linear_search__find(
        ITEMS,
        ITEMS_COUNT,
        NULL,
        ITEM_SIZE,
        &item_compare);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INVALID, result__error(result));
    PASS();
}

TEST linear_search__find___item_size_is_invalid___result_is_failure_with_item_size_invalid_error(void) {
    const uint32_t item = 3;

    const linear_search__item_index_result result = linear_search__find(
        ITEMS,
        ITEMS_COUNT,
        &item,
        0,
        &item_compare);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_SIZE_INVALID, result__error(result));
    PASS();
}

TEST linear_search__find___item_compare_is_invalid___result_is_failure_with_item_compare_invalid_error(void) {
    const uint32_t item = 3;

    const linear_search__item_index_result result = linear_search__find(
        ITEMS,
        ITEMS_COUNT,
        &item,
        ITEM_SIZE,
        NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_COMPARE_INVALID, result__error(result));
    PASS();
}

TEST linear_search__find___items_is_empty___result_is_failure_with_item_not_found_error(void) {
    const uint32_t item = 3;

    const linear_search__item_index_result result = linear_search__find(
        ITEMS_EMPTY,
        ITEMS_EMPTY_COUNT,
        &item,
        ITEM_SIZE,
        &item_compare);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_NOT_FOUND, result__error(result));
    PASS();
}

TEST linear_search__find___item_is_not_found___result_is_failure_with_item_not_found_error(void) {
    const uint32_t item = 10;

    const linear_search__item_index_result result = linear_search__find(
        ITEMS,
        ITEMS_COUNT,
        &item,
        ITEM_SIZE,
        &item_compare);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_NOT_FOUND, result__error(result));
    PASS();
}

TEST linear_search__find___item_is_found___result_is_success_with_item_found_index(void) {
    for (uint32_t item_index = 0; item_index < ITEMS_COUNT; item_index++) {
        const linear_search__item_index_result result = linear_search__find(
            ITEMS,
            ITEMS_COUNT,
            &ITEMS[item_index],
            ITEM_SIZE,
            &item_compare);

        ASSERT(result__is_success(result));
        ASSERT_EQ(item_index, result__value(result));
    }

    PASS();
}

SUITE(linear_search_suite) {
    RUN_TEST(linear_search__find___items_is_invalid___result_is_failure_with_items_invalid_error);
    RUN_TEST(linear_search__find___item_is_invalid___result_is_failure_with_item_invalid_error);
    RUN_TEST(linear_search__find___item_size_is_invalid___result_is_failure_with_item_size_invalid_error);
    RUN_TEST(linear_search__find___item_compare_is_invalid___result_is_failure_with_item_compare_invalid_error);
    RUN_TEST(linear_search__find___items_is_empty___result_is_failure_with_item_not_found_error);
    RUN_TEST(linear_search__find___item_is_not_found___result_is_failure_with_item_not_found_error);
    RUN_TEST(linear_search__find___item_is_found___result_is_success_with_item_found_index);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linear_search_suite);

    GREATEST_MAIN_END();
}
