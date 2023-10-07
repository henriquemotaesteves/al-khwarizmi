#include "greatest.h"

#include "linked-list.h"

static const uint64_t ITEM_1 = 657401;
static const uint64_t ITEM_2 = 486362;
static const uint64_t ITEM_3 = 965131;
static const uint64_t ITEM_4 = 642837;

TEST linked_list__empty___empty_list_is_created(void) {
    linked_list *list = result__value(linked_list__empty());

    const linked_list__bool_result is_empty = linked_list__is_empty(list);

    linked_list__destroy(&list);

    ASSERT(result__value(is_empty));
    PASS();
}

TEST linked_list__insert_at___list_is_empty_and_item_index_is_zero___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__item_result result = linked_list__insert_at(list, 0, (void *)&ITEM_1);

    const uint64_t  size   = result__value(linked_list__size(list));
    const uint64_t *item_1 = result__value(linked_list__at(list, 0));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__insert_at___list_is_not_empty_and_item_index_is_zero___item_is_inserted_at_start(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);

    linked_list__item_result result = linked_list__insert_at(list, 0, (void *)&ITEM_3);

    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));

    const uint64_t size = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_3, *item_1);
    ASSERT_EQ(ITEM_1, *item_2);
    ASSERT_EQ(ITEM_2, *item_3);
    PASS();
}

TEST linked_list__insert_at___list_is_not_empty_and_item_index_is_size___item_is_inserted_at_end(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);

    uint64_t size = result__value(linked_list__size(list));

    linked_list__item_result result = linked_list__insert_at(list, size, (void *)&ITEM_3);

    const uint64_t *item_1 = result__value(linked_list__at(list, 0));
    const uint64_t *item_2 = result__value(linked_list__at(list, 1));
    const uint64_t *item_3 = result__value(linked_list__at(list, 2));

    size = result__value(linked_list__size(list));

    linked_list__destroy(&list);

    ASSERT(result__is_success(result));
    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list__insert_at___list_is_not_empty_and_item_index_is_greater_than_zero_and_less_than_size___item_is_inserted_at_index(void) {
    linked_list *list = result__value(linked_list__empty());

    linked_list__insert_at_end(list, (void *)&ITEM_1);
    linked_list__insert_at_end(list, (void *)&ITEM_2);
    linked_list__insert_at_end(list, (void *)&ITEM_3);

    linked_list__item_result result = linked_list__insert_at(list, 1, (void *)&ITEM_4);

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

TEST linked_list__insert_at_start__list_is_not_empty___item_is_inserted_at_start(void) {
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

TEST linked_list__insert_at_end___list_is_not_empty___item_is_inserted_at_the_end(void) {
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

SUITE(linked_list_suite) {
    RUN_TEST(linked_list__empty___empty_list_is_created);
    RUN_TEST(linked_list__insert_at___list_is_empty_and_item_index_is_zero___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at___list_is_not_empty_and_item_index_is_zero___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at___list_is_not_empty_and_item_index_is_size___item_is_inserted_at_end);
    RUN_TEST(linked_list__insert_at___list_is_not_empty_and_item_index_is_greater_than_zero_and_less_than_size___item_is_inserted_at_index);
    RUN_TEST(linked_list__insert_at_start___list_is_empty___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at_start__list_is_not_empty___item_is_inserted_at_start);
    RUN_TEST(linked_list__insert_at_end___list_is_empty___item_is_inserted_at_the_end);
    RUN_TEST(linked_list__insert_at_end___list_is_not_empty___item_is_inserted_at_the_end);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linked_list_suite);

    GREATEST_MAIN_END();
}
