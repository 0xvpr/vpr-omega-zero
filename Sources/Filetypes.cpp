#include "Filetypes.hpp"

[[nodiscard]]
static uint16_t DetermineElfArchitecture(char* header) {

    const static unsigned char elf_magic[4] = {
        0x7f, 0x45, 0x4c, 0x46,
    };

    // Check if first bytes are 'magic'
    for (size_t i = 0; i < sizeof(elf_magic); i++) {
        if (header[i] != elf_magic[i]) {
            return filetypes::unsupported;
        }
    }

    switch (header[4]) {
        case 1:  { return filetypes::elf_x86; }
        case 2:  { return filetypes::elf_x86_64; }
        default: { break; }
    }

    return filetypes::unsupported;

}

[[nodiscard]]
uint16_t filetypes::DetermineFiletype(std::ifstream& ifs) {

    uint16_t architecture = 0;

    if (ifs.good()) {
        char header[64]{0};
        
        ifs.read(header, sizeof(header));
        if (architecture) {
            ifs.close();
            return architecture;
        } else if ((architecture = DetermineElfArchitecture(header))) {
            ifs.close();
            return architecture;
        }
    }

    ifs.close();
    return architecture;
}
