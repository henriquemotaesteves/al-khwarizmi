#ifndef _RESULT_H_
#define _RESULT_H_

#include <stdbool.h>

#define result(result_type, value_type, error_type)           \
    struct result_type##_result {                             \
        bool       success;                                   \
        value_type value;                                     \
        error_type error;                                     \
    };                                                        \
                                                              \
    typedef struct result_type##_result result_type##_result; \

#define result__success(result_type, result_value) \
    (result_type) {                                \
        .success = true,                           \
        .value   = result_value                    \
    }                                              \

#define result__failure(result_type, result_error) \
    (result_type) {                                \
        .success = false,                          \
        .error   = result_error                    \
    }                                              \

#define result__is_success(result) \
    result.success                 \

#define result__is_failure(result) \
    ! result.success               \

#define result__value(result) \
    result.value              \

#define result__error(result) \
    result.error              \

#endif // _RESULT_H_
