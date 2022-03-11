#ifndef ELF_HEADER
#define ELF_HEADER

#include <cstdint>

// Structs
namespace elf {

    typedef struct _ElfHeader32 {
        unsigned char   e_magic[16];
        uint16_t        e_type;
        uint16_t        e_machine;
        uint32_t        e_version;
        uint32_t        e_entry;
        uint32_t        e_phoff;
        uint32_t        e_shoff;
        uint32_t        e_flags;
        uint16_t        e_ehsize;
        uint16_t        e_phentsize;
        uint16_t        e_phnum;
        uint16_t        e_shentsize;
        uint16_t        e_shnum;
        uint16_t        e_shstrndx;
    } ElfHeader32;

    typedef struct _ElfHeader64 {
        unsigned char   e_magic[16];
        uint16_t        e_type;
        uint16_t        e_machine;
        uint32_t        e_version;
        uint64_t        e_entry;
        uint64_t        e_phoff;
        uint64_t        e_shoff;
        uint32_t        e_flags;
        uint16_t        e_ehsize;
        uint16_t        e_phentsize;
        uint16_t        e_phnum;
        uint16_t        e_shentsize;
        uint16_t        e_shnum;
        uint16_t        e_shstrndx;
    } ElfHeader64;

} // namespace elf

// Functions
namespace elf {

    /**
     * Perform scraping of 32 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElf32(char*);

    /**
     * Perform scraping of 64 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElf64(char*);

} // namespace elf

#endif // ELF_HEADER
