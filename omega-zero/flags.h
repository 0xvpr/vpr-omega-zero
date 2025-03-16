#ifndef   FLAGS_HEADER
#define   FLAGS_HEADER

#include <stdbool.h>

typedef struct _flags {
    bool zero_all:1;
    bool zero_headers:1;
    bool zero_section_headers:1;
    bool zero_optional_headers:1;
} flags_t, *flags_ptr_t;

#endif // FLAGS_HEADER
