#ifndef ELF_HEADER
#define ELF_HEADER

#include <stdbool.h>
#include <stdint.h>

#include "flags.h"

// Structs
typedef struct _ElfHeader32 {
    uint8_t  e_magic[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} ElfHeader32;

typedef struct _ElfHeader64 {
    uint8_t  e_magic[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} ElfHeader64;

// Functions
/**
 * Perform scraping of 32 bit ELF binary.
 *
 * @param    filename
 * @return   success
**/
bool process_elf32(const char * restrict, const flags_ptr_t);

/**
 * Perform scraping of 64 bit ELF binary.
 *
 * @param    filename
 * @return   success
**/
bool process_elf64(const char * restrict, const flags_ptr_t);

#endif // ELF_HEADER
