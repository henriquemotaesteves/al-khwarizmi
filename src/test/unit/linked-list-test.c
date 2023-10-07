#include "greatest.h"

#include "linked-list.h"

TEST linked_list_create__always__returns_an_empty_list(void) {
    linked_list * list = linked_list_create();

    ASSERT(linked_list_is_empty(list));
    PASS();
}

SUITE(linear_search_suite) {
    RUN_TEST(linked_list_create__always__returns_an_empty_list);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(linear_search_suite);

    GREATEST_MAIN_END();
}