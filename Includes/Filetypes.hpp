#ifndef FILETYPE_HEADER
#define FILETYPE_HEADER

#include <fstream>
#include <cstdint>

namespace filetypes {

    enum {
        unsupported,   // 0
        pe_x86,        // 1
        pe_x86_64,     // 2
        elf_x86,       // 3
        elf_x86_64     // 4
    };

    /**
     * Determine which executable format the file is compliant with.
     *
     * @param    header
     * @return
    **/
    [[nodiscard]] uint16_t DetermineFiletype(std::ifstream&);

}

#endif // FILETYPE_HEADER
