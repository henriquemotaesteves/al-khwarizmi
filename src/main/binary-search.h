#ifndef _BINARY_SEARCH_
#define _BINARY_SEARCH_

#include <stdlib.h>

#include "ordering.h"
#include "status.h"

#define COMPARE_IS_NULL             (ERROR | 0x00000001)
#define ITEM_IS_NULL                (ERROR | 0x00000002)
#define NUMBER_OF_ITEMS_IS_NEGATIVE (ERROR | 0x00000003)
#define ITEM_SIZE_IS_INVALID        (ERROR | 0x00000004)
#define ITEM_TO_FOUND_IS_NULL       (ERROR | 0x00000005)
#define INDEX_OF_FOUND_ITEM_IS_NULL (ERROR | 0x00000006)
#define ITEM_NOT_FOUND              (ERROR | 0x00000007)

status binary_search(const ordering_compare compare, const void *items, const size_t number_of_items, const size_t item_size, const void *item_to_found, size_t *index_of_found_item);

#endif // _BINARY_SEARCH_
