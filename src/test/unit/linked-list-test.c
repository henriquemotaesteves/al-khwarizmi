#include "greatest.h"

#include "linked-list.h"

static const uint64_t ITEM_1 = 657401;
static const uint64_t ITEM_2 = 486362;
static const uint64_t ITEM_3 = 965131;

TEST linked_list_create__always__returns_an_empty_list(void) {
    linked_list *list = linked_list_create();

    bool empty = linked_list_is_empty(list);

    linked_list_destroy(&list);

    ASSERT(empty);
    PASS();
}

TEST linked_list_append__if_list_is_empty__(void) {
    linked_list *list = linked_list_create();

    linked_list_append(list, (void *)&ITEM_1);

    uint64_t  size   = linked_list_size(list);
    uint64_t *item_1 = linked_list_get(list, 0);

    linked_list_destroy(&list);

    ASSERT_EQ(1,      size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list_append__if_list_is_not_empty__(void) {
    linked_list *list = linked_list_create();

    linked_list_append(list, (void *)&ITEM_1);
    linked_list_append(list, (void *)&ITEM_2);
    linked_list_append(list, (void *)&ITEM_3);

    uint64_t  size   = linked_list_size(list);
    uint64_t *item_1 = linked_list_get(list, 0);
    uint64_t *item_2 = linked_list_get(list, 1);
    uint64_t *item_3 = linked_list_get(list, 2);

    linked_list_destroy(&list);

    ASSERT_EQ(3,      size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

TEST linked_list_prepend__if_list_is_empty__(void) {
    linked_list *list = linked_list_create();

    linked_list_prepend(list, (void *)&ITEM_1);

    uint64_t  size   = linked_list_size(list);
    uint64_t *item_1 = linked_list_get(list, 0);

    linked_list_destroy(&list);

    ASSERT_EQ(1,      size);
    ASSERT_EQ(ITEM_1, *item_1);
    PASS();
}

TEST linked_list_prepend__if_list_is_not_empty__(void) {
    linked_list *list = linked_list_create();

    linked_list_prepend(list, (void *)&ITEM_1);
    linked_list_prepend(list, (void *)&ITEM_2);
    linked_list_prepend(list, (void *)&ITEM_3);

    uint64_t  size   = linked_list_size(list);
    uint64_t *item_1 = linked_list_get(list, 2);
    uint64_t *item_2 = linked_list_get(list, 1);
    uint64_t *item_3 = linked_list_get(list, 0);

    linked_list_destroy(&list);

    ASSERT_EQ(3,      size);
    ASSERT_EQ(ITEM_1, *item_1);
    ASSERT_EQ(ITEM_2, *item_2);
    ASSERT_EQ(ITEM_3, *item_3);
    PASS();
}

SUITE(linked_list_suite) {
    RUN_TEST(linked_list_create__always__returns_an_empty_list);
    RUN_TEST(linked_list_append__if_list_is_empty__);
    RUN_TEST(linked_list_append__if_list_is_not_empty__);
    RUN_TEST(linked_list_prepend__if_list_is_empty__);
    RUN_TEST(linked_list_prepend__if_list_is_not_empty__);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linked_list_suite);

    GREATEST_MAIN_END();
}