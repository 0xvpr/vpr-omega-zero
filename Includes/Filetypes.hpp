#ifndef FILETYPE_HEADER
#define FILETYPE_HEADER

namespace filetype {
    enum {
        unsupported,   // 0
        pe_x86,        // 1
        pe_x86_64,     // 2
        elf_x86,       // 3
        elf_x86_64     // 4
    };
}

#endif // FILETYPE_HEADER
