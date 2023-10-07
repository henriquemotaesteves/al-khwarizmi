#ifndef GREATEST_ASSERTION_H_
#define GREATEST_ASSERTION_H_

#include "greatest.h"

#define ASSERT_RESULT_IS_SUCCESS(result_actual)  \
    ASSERT(result__is_success(result_actual));   \

#define ASSERT_RESULT_IS_FAILURE_WITH_ERROR(error_expected, result_actual)  \
    ASSERT(result__is_failure(result_actual));                              \
                                                                            \
    ASSERT_EQ(error_expected, result__error(result_actual));                \

#define ASSERT_RESULT_IS_SUCCESS_WITH_UINT64(value_expected, result_actual) \
    ASSERT(result__is_success(result_actual));                              \
                                                                            \
    ASSERT_EQ(value_expected, result__value(result_actual));                \

#define ASSERT_RESULT_IS_SUCCESS_WITH_UINT64_POINTER(value_expected, result_actual) \
    ASSERT(result__is_success(result_actual));                                      \
                                                                                    \
    ASSERT_EQ(value_expected, *(uint64_t *)result__value(result_actual));           \

#endif // GREATEST_ASSERTION_H_
