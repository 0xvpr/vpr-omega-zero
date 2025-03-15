#ifndef   FLAGS_HEADER
#define   FLAGS_HEADER

#include <stdbool.h>

typedef struct _flags {
    bool zero_headers;
    bool zero_sections;
    bool zero_all;
} flags_t, *flags_ptr_t;

#endif // FLAGS_HEADER
