#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "greatest.h"

#include "linked-list.h"

#include "result.h"

static const uint64_t ITEM_1 = 657401;
static const uint64_t ITEM_2 = 486362;
static const uint64_t ITEM_3 = 965131;
static const uint64_t ITEM_4 = 642837;

bool item__equals(const void *item, const void *item_other) {
    const uint64_t *item_typed       = item;
    const uint64_t *item_other_typed = item_other;

    return *item_typed == *item_other_typed;
}

TEST linked_list__empty___empty_list_is_created(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    linked_list__destroy(&list);

    ASSERT(result__value(is_empty));
    PASS();
}

TEST linked_list__destroy___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    linked_list *list = NULL;

    const linked_list__list_result result_1 = linked_list__destroy(NULL);
    const linked_list__list_result result_2 = linked_list__destroy(&list);

    ASSERT(result__is_failure(result_1));
    ASSERT_EQ(LIST_INVALID, result__error(result_1));

    ASSERT(result__is_failure(result_2));
    ASSERT_EQ(LIST_INVALID, result__error(result_2));

    PASS();
}

TEST linked_list__clear___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__size_result result = linked_list__clear(NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__clear___list_is_empty___no_items_are_removed(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__size_result result = linked_list__clear(list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(0, result__value(result));

    ASSERT(result__value(linked_list__is_empty(list)));

    PASS();
}

TEST linked_list__clear___list_has_single_item___single_item_is_removed(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);

    const linked_list__size_result result = linked_list__clear(list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(1, result__value(result));

    ASSERT(result__value(linked_list__is_empty(list)));

    PASS();
}

TEST linked_list__clear___list_has_multiple_items___all_items_are_removed(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__size_result result = linked_list__clear(list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(3, result__value(result));

    ASSERT(result__value(linked_list__is_empty(list)));

    PASS();
}

TEST linked_list__at___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__at(NULL, 0);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__index_of___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    // Arrange
    const linked_list *list = NULL;

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_1, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);

    ASSERT(is_failure);
    ASSERT_EQ(LIST_INVALID, error);
    PASS();
}

TEST linked_list__index_of___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_as_error(void) {
    // Arrange
    const linked_list *list = result__value(linked_list__empty());

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_1, NULL);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_EQUALS_INVALID, error);
    PASS();
}

TEST linked_list__index_of___list_is_empty___result_is_failure_with_item_not_found_as_error(void) {
    // Arrange
    const linked_list *list = result__value(linked_list__empty());

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_1, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_NOT_FOUND, error);
    PASS();
}

TEST linked_list__index_of___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_found_item_index_as_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_1, item__equals);

    // Assert
    const bool     is_success       = result__is_success(result);
    const uint64_t item_index_found = result__value(result);

    ASSERT(is_success);
    ASSERT_EQ(0, item_index_found);
    PASS();
}

TEST linked_list__index_of___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_failure_with_item_not_found_as_error(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_4, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_NOT_FOUND, error);
    PASS();
}

TEST linked_list__index_of___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_3, item__equals);

    // Assert
    const bool     is_success       = result__is_success(result);
    const uint64_t item_index_found = result__value(result);

    ASSERT(is_success);
    ASSERT_EQ(2, item_index_found);
    PASS();
}

TEST linked_list__index_of___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_failure_with_item_not_found_as_error(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    // Act
    const linked_list__item_index_result result = linked_list__index_of(list, &ITEM_4, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_NOT_FOUND, error);
    PASS();
}

TEST linked_list__insert_at___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__insert_at(NULL, 0, (void *)&ITEM_1);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at___item_is_invalid___result_is_failure_with_item_invalid_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__insert_at(list, 0, NULL);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at___list_is_empty_and_item_index_is_zero___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__insert_at(list, 0, (void *)&ITEM_1);

    const uint64_t  size   = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__insert_at___list_is_empty_and_item_index_is_greater_than_zero___result_is_failure_with_item_index_of_bounds_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__insert_at(list, 1, (void *)&ITEM_1);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INDEX_OUT_OF_BOUNDS, result__error(result));
    PASS();
}

TEST linked_list__insert_at___list_has_multiple_items_and_item_index_is_equal_to_zero___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__item_result result = linked_list__insert_at(list, 0, (void *)&ITEM_4);

    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));
    const uint64_t *item_4 = result__value(linked_list__at(list, 3));

    const uint64_t size = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(4, size);
    ASSERT_EQ(ITEM_4, *item_1);
    ASSERT_EQ(ITEM_1, *item_2);
    ASSERT_EQ(ITEM_2, *item_3);
    ASSERT_EQ(ITEM_3, *item_4);
    PASS();
}

TEST linked_list__insert_at___list_has_multiple_items_and_item_index_is_equal_to_size___item_is_inserted_at_end(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    uint64_t size = result__value(linked_list__size(list));

    const linked_list__item_result result = linked_list__insert_at(list, size, (void *)&ITEM_4);

    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));
    const uint64_t *item_4 = result__value(linked_list__at(list, 3));

    size = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(4, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    ASSERT_EQ(ITEM_4, *item_4);
    PASS();
}

TEST linked_list__insert_at___list_has_multiple_items_and_item_index_is_greater_than_zero_and_less_than_size___item_is_inserted_at_index(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__item_result result = linked_list__insert_at(list, 1, (void *)&ITEM_4);

    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));
    const uint64_t *item_4 = result__value(linked_list__at(list, 3));

    const uint64_t size = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(4, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_4, *item_2);
    ASSERT_EQ(ITEM_2, *item_3);
    ASSERT_EQ(ITEM_3, *item_4);
    PASS();
}

TEST linked_list__insert_at___list_has_multiple_items_and_item_index_is_greater_than_size___result_is_failure_with_item_index_of_bounds_error(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    uint64_t size = result__value(linked_list__size(list));

    const linked_list__item_result result = linked_list__insert_at(list, size + 1, (void *)&ITEM_4);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INDEX_OUT_OF_BOUNDS, result__error(result));
    PASS();
}

TEST linked_list__insert_at_start___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__insert_at_start(NULL, (void *)&ITEM_1);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at_start___item_is_invalid___result_is_failure_with_item_invalid_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__insert_at_start(list, NULL);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at_start___list_is_empty___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);

    const uint64_t size    = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));

    linked_list__destroy(&list);

    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__insert_at_start___list_has_multiple_items___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    const uint64_t size    = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));

    linked_list__destroy(&list);

    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_3, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_1, *item_3);
    PASS();
}

TEST linked_list__insert_at_end___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__insert_at_end(NULL, (void *)&ITEM_1);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at_end___item_is_invalid___result_is_failure_with_item_invalid_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__insert_at_end(list, NULL);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INVALID, result__error(result));
    PASS();
}

TEST linked_list__insert_at_end___list_is_empty___item_is_inserted_at_the_end(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);

    const uint64_t  size   = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));

    linked_list__destroy(&list);

    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__insert_at_end___list_has_multiple_items___item_is_inserted_at_the_end(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const uint64_t size    = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));

    linked_list__destroy(&list);

    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list__remove___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__remove(NULL, (void *)&ITEM_1, item__equals);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__remove___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__remove(list, &ITEM_1, NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_EQUALS_INVALID, result__error(result));
    PASS();
}

TEST linked_list__remove___list_is_empty___result_is_failure_with_item_not_found_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__item_result result = linked_list__remove(list, &ITEM_1, item__equals);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_NOT_FOUND, result__error(result));
    PASS();
}

TEST linked_list__remove___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);

    // Act
    const linked_list__item_result result = linked_list__remove(list, &ITEM_1, item__equals);

    // Assert
    const bool     is_success    = result__is_success(result);
    const uint64_t *item_removed = result__value(result);
    const uint64_t list_size     = result__value(linked_list__size(list));

    ASSERT(is_success);
    ASSERT_EQ(ITEM_1, *item_removed);
    ASSERT_EQ(0, list_size);
    PASS();
}

TEST linked_list__remove___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_failure_with_item_not_found_as_error(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);

    // Act
    const linked_list__item_result result = linked_list__remove(list, &ITEM_4, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);
    const uint64_t           list_size  = result__value(linked_list__size(list));

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_NOT_FOUND, error);
    ASSERT_EQ(1, list_size);
    PASS();
}

TEST linked_list__remove___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    // Act
    const linked_list__item_result result = linked_list__remove(list, &ITEM_3, item__equals);

    // Assert
    const bool     is_success    = result__is_success(result);
    const uint64_t *item_removed = result__value(result);
    const uint64_t list_size     = result__value(linked_list__size(list));

    ASSERT(is_success);
    ASSERT_EQ(ITEM_3, *item_removed);
    ASSERT_EQ(2, list_size);
    PASS();
}

TEST linked_list__remove___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_failure_with_item_not_found_as_error(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    // Act
    const linked_list__item_result result = linked_list__remove(list, &ITEM_4, item__equals);

    // Assert
    const bool               is_failure = result__is_failure(result);
    const linked_list__error error      = result__error(result);
    const uint64_t           list_size  = result__value(linked_list__size(list));

    ASSERT(is_failure);
    ASSERT_EQ(ITEM_NOT_FOUND, error);
    ASSERT_EQ(3, list_size);
    PASS();
}

TEST linked_list__remove_at___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__remove_at(NULL, 0);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__remove_at___list_is_empty___result_is_failure_with_item_index_of_bounds_error(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__item_result result = linked_list__remove_at(list, 0);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INDEX_OUT_OF_BOUNDS, result__error(result));
    PASS();
}

TEST linked_list__remove_at___list_has_multiple_items_and_item_index_is_start___item_is_removed_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__item_result result = linked_list__remove_at(list, 0);

    const uint64_t *item = result__value(result);
    const uint64_t size  = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(ITEM_1, *item);
    ASSERT_EQ(2, size);
    PASS();
}

TEST linked_list__remove_at___list_has_multiple_items_and_item_index_is_end___item_is_removed_at_end(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__item_result result = linked_list__remove_at(list, 2);

    const uint64_t *item = result__value(result);
    const uint64_t size  = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(ITEM_3, *item);
    ASSERT_EQ(2, size);
    PASS();
}

TEST linked_list__remove_at___list_has_multiple_items_and_item_index_is_not_start_or_end___item_is_removed_at_index(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const linked_list__item_result result = linked_list__remove_at(list, 1);

    const uint64_t *item = result__value(result);
    const uint64_t size  = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(ITEM_2, *item);
    ASSERT_EQ(2, size);
    PASS();
}

TEST linked_list__remove_at_start___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__remove_at_start(NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__remove_at_start___list_is_empty___result_is_failure_with_item_index_of_bounds_error(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__item_result result = linked_list__remove_at_start(list);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INDEX_OUT_OF_BOUNDS, result__error(result));
    PASS();
}

TEST linked_list__remove_at_start___list_has_multiple_items___item_is_removed_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    const uint64_t *item_1 = result__value(linked_list__remove_at_start(list));
    const uint64_t *item_2 = result__value(linked_list__remove_at_start(list));
    const uint64_t *item_3 = result__value(linked_list__remove_at_start(list));
    const uint64_t size    = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT_EQ(0, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list__remove_at_end___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__item_result result = linked_list__remove_at_start(NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__remove_at_end___list_is_empty___result_is_failure_with_item_index_of_bounds_error(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__item_result result = linked_list__remove_at_end(list);

    linked_list__destroy(&list);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_INDEX_OUT_OF_BOUNDS, result__error(result));
    PASS();
}

TEST linked_list__remove_at_end___list_has_multiple_items___item_is_removed_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    const uint64_t *item_1 = result__value(linked_list__remove_at_end(list));
    const uint64_t *item_2 = result__value(linked_list__remove_at_end(list));
    const uint64_t *item_3 = result__value(linked_list__remove_at_end(list));
    const uint64_t size    = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT_EQ(0, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list__contains___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__bool_result result = linked_list__contains(NULL, &ITEM_1, item__equals);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__contains___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_error(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__bool_result result = linked_list__contains(list, &ITEM_1, NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(ITEM_EQUALS_INVALID, result__error(result));
    PASS();
}

TEST linked_list__contains___list_is_empty___result_is_success_with_false_value(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__bool_result result = linked_list__contains(list, &ITEM_1, item__equals);

    ASSERT(result__is_success(result));
    ASSERT_FALSE(result__value(result));
    PASS();
}

TEST linked_list__contains___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_true_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);

    // Act
    const linked_list__bool_result result = linked_list__contains(list, &ITEM_1, item__equals);

    // Assert
    ASSERT(result__is_success(result));
    ASSERT(result__value(result));
    PASS();
}

TEST linked_list__contains___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_success_with_false_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);

    // Act
    const linked_list__bool_result result = linked_list__contains(list, &ITEM_1, item__equals);

    // Assert
    ASSERT(result__is_success(result));
    ASSERT(result__value(result));
    PASS();
}

TEST linked_list__contains___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_true_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    // Act
    const linked_list__bool_result result = linked_list__contains(list, &ITEM_3, item__equals);

    // Assert
    ASSERT(result__is_success(result));
    ASSERT(result__value(result));
    PASS();
}

TEST linked_list__contains___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_success_with_false_value(void) {
    // Arrange
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_start(list, (void *)&ITEM_1);
    linked_list__insert_at_start(list, (void *)&ITEM_2);
    linked_list__insert_at_start(list, (void *)&ITEM_3);

    // Act
    const linked_list__bool_result result = linked_list__contains(list, &ITEM_4, item__equals);

    // Assert
    ASSERT(result__is_success(result));
    ASSERT_FALSE(result__value(result));
    PASS();
}

TEST linked_list__is_empty___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__bool_result result = linked_list__is_empty(NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

TEST linked_list__size___list_is_invalid___result_is_failure_with_list_invalid_error(void) {
    const linked_list__size_result result = linked_list__size(NULL);

    ASSERT(result__is_failure(result));
    ASSERT_EQ(LIST_INVALID, result__error(result));
    PASS();
}

SUITE(linked_list_suite) {
    RUN_TEST(linked_list__empty___empty_list_is_created);

    RUN_TEST(linked_list__destroy___list_is_invalid___result_is_failure_with_list_invalid_error);

    RUN_TEST(linked_list__clear___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__clear___list_is_empty___no_items_are_removed);
    RUN_TEST(linked_list__clear___list_has_single_item___single_item_is_removed);
    RUN_TEST(linked_list__clear___list_has_multiple_items___all_items_are_removed);

    RUN_TEST(linked_list__at___list_is_invalid___result_is_failure_with_list_invalid_error);

    RUN_TEST(linked_list__index_of___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__index_of___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_as_error);
    RUN_TEST(linked_list__index_of___list_is_empty___result_is_failure_with_item_not_found_as_error);
    RUN_TEST(linked_list__index_of___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_found_item_index_as_value);
    RUN_TEST(linked_list__index_of___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_failure_with_item_not_found_as_error);
    RUN_TEST(linked_list__index_of___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value);
    RUN_TEST(linked_list__index_of___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_failure_with_item_not_found_as_error);

    RUN_TEST(linked_list__insert_at___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__insert_at___item_is_invalid___result_is_failure_with_item_invalid_error);
    RUN_TEST(linked_list__insert_at___list_is_empty_and_item_index_is_zero___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at___list_is_empty_and_item_index_is_greater_than_zero___result_is_failure_with_item_index_of_bounds_error);
    RUN_TEST(linked_list__insert_at___list_has_multiple_items_and_item_index_is_equal_to_zero___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at___list_has_multiple_items_and_item_index_is_equal_to_size___item_is_inserted_at_end);
    RUN_TEST(linked_list__insert_at___list_has_multiple_items_and_item_index_is_greater_than_zero_and_less_than_size___item_is_inserted_at_index);
    RUN_TEST(linked_list__insert_at___list_has_multiple_items_and_item_index_is_greater_than_size___result_is_failure_with_item_index_of_bounds_error);

    RUN_TEST(linked_list__insert_at_start___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__insert_at_start___item_is_invalid___result_is_failure_with_item_invalid_error);
    RUN_TEST(linked_list__insert_at_start___list_is_empty___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at_start___list_has_multiple_items___item_is_inserted_at_start);

    RUN_TEST(linked_list__insert_at_end___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__insert_at_end___item_is_invalid___result_is_failure_with_item_invalid_error);
    RUN_TEST(linked_list__insert_at_end___list_is_empty___item_is_inserted_at_the_end);
    RUN_TEST(linked_list__insert_at_end___list_has_multiple_items___item_is_inserted_at_the_end);

    RUN_TEST(linked_list__remove___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__remove___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_error);
    RUN_TEST(linked_list__remove___list_is_empty___result_is_failure_with_item_not_found_error);
    RUN_TEST(linked_list__remove___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value);
    RUN_TEST(linked_list__remove___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_failure_with_item_not_found_as_error);
    RUN_TEST(linked_list__remove___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_removed_item_as_value);
    RUN_TEST(linked_list__remove___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_failure_with_item_not_found_as_error);

    RUN_TEST(linked_list__remove_at___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__remove_at___list_is_empty___result_is_failure_with_item_index_of_bounds_error);
    RUN_TEST(linked_list__remove_at___list_has_multiple_items_and_item_index_is_start___item_is_removed_at_start);
    RUN_TEST(linked_list__remove_at___list_has_multiple_items_and_item_index_is_end___item_is_removed_at_end);
    RUN_TEST(linked_list__remove_at___list_has_multiple_items_and_item_index_is_not_start_or_end___item_is_removed_at_index);

    RUN_TEST(linked_list__remove_at_start___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__remove_at_start___list_is_empty___result_is_failure_with_item_index_of_bounds_error);
    RUN_TEST(linked_list__remove_at_start___list_has_multiple_items___item_is_removed_at_start);

    RUN_TEST(linked_list__remove_at_end___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__remove_at_end___list_is_empty___result_is_failure_with_item_index_of_bounds_error);
    RUN_TEST(linked_list__remove_at_end___list_has_multiple_items___item_is_removed_at_start);

    RUN_TEST(linked_list__contains___list_is_invalid___result_is_failure_with_list_invalid_error);
    RUN_TEST(linked_list__contains___item_equals_is_invalid___result_is_failure_with_item_equals_invalid_error);
    RUN_TEST(linked_list__contains___list_is_empty___result_is_success_with_false_value);
    RUN_TEST(linked_list__contains___list_has_single_item_and_list_contains_the_specified_item___result_is_success_with_true_value);
    RUN_TEST(linked_list__contains___list_has_single_item_and_list_does_not_contain_the_specified_item___result_is_success_with_false_value);
    RUN_TEST(linked_list__contains___list_has_multiple_items_and_list_contains_the_specified_item___result_is_success_with_true_value);
    RUN_TEST(linked_list__contains___list_has_multiple_items_and_list_does_not_contains_the_specified_item___result_is_success_with_false_value);

    RUN_TEST(linked_list__is_empty___list_is_invalid___result_is_failure_with_list_invalid_error);

    RUN_TEST(linked_list__size___list_is_invalid___result_is_failure_with_list_invalid_error);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linked_list_suite);

    GREATEST_MAIN_END();
}
