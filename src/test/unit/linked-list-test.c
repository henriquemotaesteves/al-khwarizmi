#include "greatest.h"

#include "linked-list.h"

static const uint64_t ITEM_1 = 657401;
static const uint64_t ITEM_2 = 486362;
static const uint64_t ITEM_3 = 965131;

TEST linked_list__empty___empty_list_is_created(void) {
    linked_list *list = linked_list__empty();

    const bool empty = linked_list__is_empty(list);

    linked_list__destroy(&list);

    ASSERT(empty);
    PASS();
}

TEST linked_list__add_at_end___list_is_empty___item_is_added_at_the_end(void) {
    linked_list *list = linked_list__empty();

    linked_list__add_at_start(list, (void *)&ITEM_1);

    const uint64_t  size   = linked_list__size(list);
    const uint64_t *item_1 = linked_list__at(list, 0);

    linked_list__destroy(&list);

    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__add_at_end___list_is_not_empty___item_is_added_at_the_end(void) {
    linked_list *list = linked_list__empty();

    linked_list__add_at_start(list, (void *)&ITEM_1);
    linked_list__add_at_start(list, (void *)&ITEM_2);
    linked_list__add_at_start(list, (void *)&ITEM_3);

    const uint64_t  size   = linked_list__size(list);
    const uint64_t *item_1 = linked_list__at(list, 0);
    const uint64_t *item_2 = linked_list__at(list, 1);
    const uint64_t *item_3 = linked_list__at(list, 2);

    linked_list__destroy(&list);

    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list__add_at_start___list_is_empty___item_is_added_at_the_beginning(void) {
    linked_list *list = linked_list__empty();

    linked_list__add_at_end(list, (void *)&ITEM_1);

    const uint64_t  size   = linked_list__size(list);
    const uint64_t *item_1 = linked_list__at(list, 0);

    linked_list__destroy(&list);

    ASSERT_EQ(1, size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list__add_at_start__list_is_not_empty___item_is_added_at_the_beginning(void) {
    linked_list *list = linked_list__empty();

    linked_list__add_at_end(list, (void *)&ITEM_1);
    linked_list__add_at_end(list, (void *)&ITEM_2);
    linked_list__add_at_end(list, (void *)&ITEM_3);

    const uint64_t  size   = linked_list__size(list);
    const uint64_t *item_1 = linked_list__at(list, 2);
    const uint64_t *item_2 = linked_list__at(list, 1);
    const uint64_t *item_3 = linked_list__at(list, 0);

    linked_list__destroy(&list);

    ASSERT_EQ(3, size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

SUITE(linked_list_suite) {
    RUN_TEST(linked_list__empty___empty_list_is_created);
    RUN_TEST(linked_list__add_at_end___list_is_empty___item_is_added_at_the_end);
    RUN_TEST(linked_list__add_at_end___list_is_not_empty___item_is_added_at_the_end);
    RUN_TEST(linked_list__add_at_start___list_is_empty___item_is_added_at_the_beginning);
    RUN_TEST(linked_list__add_at_start__list_is_not_empty___item_is_added_at_the_beginning);
}

GREATEST_MAIN_DEFS();

int main(const int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linked_list_suite);

    GREATEST_MAIN_END();
}