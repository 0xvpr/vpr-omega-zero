#ifndef FILETYPES_HEADER
#define FILETYPES_HEADER

#include <stdint.h>
#include <stdio.h>

enum filetype_t {
    unsupported = 0, // 0
    pe_x86,          // 1
    pe_x86_64,       // 2
    elf_x86,         // 3
    elf_x86_64       // 4
};

/**
 * Determine which executable format the file is compliant with.
 *
 * @param    header
 * @return
**/
enum filetype_t determine_filetype(const char * restrict);

#endif // FILETYPES_HEADER
