#ifndef ELF_TYPES_HEADER
#define ELF_TYPES_HEADER

#include <fstream>

namespace elftypes {

    [[nodiscard]]
    uint16_t DetermineElfArchitecture(char*);

    [[nodiscard]]
    uint16_t DetermineFiletype(std::ifstream&);

    void ProcessElfx86(char*);
    void ProcessElfx86_64(char*);

}

#endif // ELF_TYPES_HEADER
