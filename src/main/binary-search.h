#ifndef _BINARY_SEARCH_
#define _BINARY_SEARCH_

#include <stdlib.h>

#include "ordering.h"
#include "status.h"

#define ITEMS_INVALID_ERROR        (ERROR | 0x00000001)
#define ITEM_INVALID_ERROR         (ERROR | 0x00000002)
#define ITEM_SIZE_INVALID_ERROR    (ERROR | 0x00000003)
#define ITEM_COMPARE_INVALID_ERROR (ERROR | 0x00000004)
#define ITEM_INDEX_INVALID_ERROR   (ERROR | 0x00000005)
#define ITEM_NOT_FOUND_ERROR       (ERROR | 0x00000006)

status binary_search(
    const void *           items,
    const size_t           items_count,
    const void *           item,
    const size_t           item_size,
    const ordering_compare item_compare,
    size_t *               item_index
);

#endif // _BINARY_SEARCH_
