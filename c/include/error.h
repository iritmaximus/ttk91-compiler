#ifndef ERROR_H
#define ERROR_H

typedef enum {
    VARIABLE_NULL=1,
    SWITCH_NOT_MATCHED,
    PARSE_ERROR,
    FILE_ERROR,
    ALLOC_FAILED
} error_t;

#endif
