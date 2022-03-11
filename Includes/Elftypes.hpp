#ifndef ELF_TYPES_HEADER
#define ELF_TYPES_HEADER

#include <cstdint>

// Structs
namespace elftypes {

    typedef struct {
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

    typedef struct {
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

} // namespace elftypes

namespace elftypes {

    /**
     * Perform scraping of 32 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElfx86(char*);

    /**
     * Perform scraping of 64 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElfx86_64(char*);

} // namespace elftypes

#endif // ELF_TYPES_HEADER
