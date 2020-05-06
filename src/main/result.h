#ifndef RESULT_H_
#define RESULT_H_

#include <stdbool.h>

#define result(result_type, value_type, error_type)                                      \
    struct result_type##_result {                                                        \
        bool       success;                                                              \
        value_type value;                                                                \
        error_type error;                                                                \
    };                                                                                   \
                                                                                         \
    typedef struct result_type##_result result_type##_result;                            \
                                                                                         \
    static inline result_type##_result result_type##_result__success(value_type value) { \
        return (result_type##_result) {                                                  \
            .success = true,                                                             \
            .value   = value                                                             \
        };                                                                               \
    }                                                                                    \
                                                                                         \
    static inline result_type##_result result_type##_result__failure(error_type error) { \
        return (result_type##_result) {                                                  \
            .success = false,                                                            \
            .error   = error                                                             \
        };                                                                               \
    }                                                                                    \

#define result__is_success(result) \
    result.success                 \

#define result__is_failure(result) \
    ! result.success             \

#define result__value(result) \
    result.value              \

#define result__error(result) \
    result.error              \

#endif // RESULT_H_
