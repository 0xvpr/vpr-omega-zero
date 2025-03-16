#include "filetypes.h"
#include "pe32.h"

static
uint16_t determine_pe32_architecture(FILE* fp)
{
    char header[sizeof(MsDosStub) + sizeof(Pe32Header) + sizeof(Pe32OptionalHeader)] = { 0 };

    fseek(fp, 0, SEEK_SET);
    if ( fread(header, sizeof(header), 1, fp) != 1 )
    {
        return unsupported;
    }

    if (header[0] != 'M' || header[1] != 'Z')
    {
        return unsupported;
    }

    Pe32OptionalHeader* optional_header =
        (Pe32OptionalHeader *)(header + sizeof(MsDosStub) + sizeof(Pe32Header));
    switch (optional_header->mMagic >> 9)
    {
    case  0: { return pe_x86;    }
    case  1: { return pe_x86_64; }
    default: { break;                       }
    } 

    return unsupported;

}

static
enum filetype_t determine_elf_architecture(FILE* fp)
{
    char header[8] = {0};

    fseek(fp, 0, SEEK_SET);
    if ( fread(header, sizeof(header), 1, fp) != 1 )
    {
        return unsupported;
    }

    if (header[0] != 0x7F || header[1] != 'E' || header[2] != 'L' || header[3] != 'F') {
        return unsupported;
    }

    switch (header[4])
    {
    case 1:  { return elf_x86; }
    case 2:  { return elf_x86_64; }
    default: { break; }
    }

    return unsupported;

}

enum filetype_t determine_filetype(const char * restrict filename) {

    FILE* fp = 0;
    if ( !(fp = fopen(filename, "rb")) )
    {
        return unsupported;
    }

    uint32_t architecture = 0;
    architecture = determine_pe32_architecture(fp) + determine_elf_architecture(fp);
    fclose(fp);

    return architecture;
}
