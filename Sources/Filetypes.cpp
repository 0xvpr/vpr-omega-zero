#include "Filetypes.hpp"
#include "Pe32.hpp"

#include <iostream>

[[nodiscard]]
static uint16_t DeterminePe32Architecture(std::ifstream& ifs) {

    using pe32::Pe32OptionalHeader;
    using pe32::Pe32Header;
    using pe32::MsDosStub;

    const size_t size = sizeof(MsDosStub) +
        sizeof(Pe32Header) + sizeof(Pe32OptionalHeader);
    char header[size]{0};

    ifs.seekg(0, std::ios::beg);
    ifs.read(header, sizeof(header));

    if (header[0] != 'M' || header[1] != 'Z') {
        return filetypes::unsupported;
    }

    auto optional_header = (pe32::Pe32OptionalHeader *)(header +
        sizeof(MsDosStub) + sizeof(Pe32Header));
    switch (optional_header->mMagic >> 9) {
        case  0: { return filetypes::pe_x86;    }
        case  1: { return filetypes::pe_x86_64; }
        default: { break;                       }
    } 

    return filetypes::unsupported;

}

[[nodiscard]]
static uint16_t DetermineElfArchitecture(std::ifstream& ifs) {

    char header[8]{0};
    ifs.seekg(0, std::ios::beg);
    ifs.read(header, sizeof(header));

    if (header[0] != 0x7F || header[1] != 'E' || header[2] != 'L' || header[3] != 'F') {
        return filetypes::unsupported;
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
        architecture = static_cast<uint16_t>(DeterminePe32Architecture(ifs) + DetermineElfArchitecture(ifs));
    }

    ifs.close();
    return architecture;
}
