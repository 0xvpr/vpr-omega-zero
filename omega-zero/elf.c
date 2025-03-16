#include "elf.h"

#include "filetypes.h"

#include <assert.h>
#include <stdlib.h>

typedef union {
    ElfHeader32 header32;
    ElfHeader64 header64;
} header_union;

bool process_elf(const char* restrict filename, flags_ptr_t flags, enum filetype_t arch)
{
    assert((arch == elf_x86) || (arch == elf_x86_64));

    if ( !(flags->zero_all || flags->zero_headers) )
    {
        fprintf(stderr, "No processing for '%s' to be completed.\n", filename);
        return 0;
    }

    FILE* fp = 0;
    header_union header = { 0 };
    size_t header_size =
        ((arch == elf_x86)    * sizeof(ElfHeader32)) +
        ((arch == elf_x86_64) * sizeof(ElfHeader64));

    // Open target file
    if ( !(fp = fopen(filename, "rb+")) )
    {
        fprintf(stderr, "Failed to open '%s' for reading.\n", filename);
        return false;
    }

    // Get header information
    fseek(fp, 0, SEEK_SET);
    size_t bytes_read = fread((unsigned char *)&header, header_size, 1, fp);
    if (bytes_read != 1) 
    {
        fprintf(stderr, "Failed to read bytes for elf header.\n");
        fclose(fp);
        return false;
    }

    if (arch == elf_x86) // 32 bit
    {
        // If file has a zeroed value, skip the file
        if ((header.header32.e_shentsize * header.header32.e_shnum) == 0) {
            fprintf(stderr, "'%s' has a invalid section header entry size and/or section header number.\n"
                            "Skipping '%s'.\n", filename, filename);
            fclose(fp);
            return false;
        }

        // Calculate total size
        size_t shsize = header.header32.e_shentsize * header.header32.e_shnum;
        unsigned char* null_bytes = (unsigned char *)calloc(1, sizeof(unsigned char) * shsize);
        if (!null_bytes)
        {
            fprintf(stderr, "Failed to allocate null-bytes.\n");
            fclose(fp);
            return false;
        }

        // Overwrite total bytes
        fseek(fp, (long)header.header32.e_shoff, SEEK_SET);
        if ( fwrite(null_bytes, (unsigned long)(shsize), 1, fp) != 1 )
        {
            free(null_bytes);
            fprintf(stderr, "Failed to overwrite section-header.\n");
            fclose(fp);
            return false;
        }
        free(null_bytes);

        // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
        header.header32.e_shoff     = 0;
        header.header32.e_shentsize = 0;
        header.header32.e_shnum     = 0;
        header.header32.e_shstrndx  = 0;
    }
    else // 64 bit
    {
        // If file has a zeroed value, skip the file
        if ((header.header64.e_shentsize * header.header64.e_shnum) == 0) {
            fprintf(stderr, "'%s' has a invalid section header entry size and/or section header number.\n"
                            "Skipping '%s'.\n", filename, filename);
            fclose(fp);
            return false;
        }

        // Calculate total size
        size_t shsize = header.header64.e_shentsize * header.header64.e_shnum;
        unsigned char* null_bytes = (unsigned char *)calloc(1, sizeof(unsigned char) * shsize);
        if (!null_bytes)
        {
            fprintf(stderr, "Failed to allocate null-bytes.\n");
            fclose(fp);
            return false;
        }

        // Overwrite total bytes
        fseek(fp, (long)header.header64.e_shoff, SEEK_SET);
        if ( fwrite(null_bytes, (unsigned long)(shsize), 1, fp) != 1 )
        {
            free(null_bytes);
            fprintf(stderr, "Failed to overwrite section-header.\n");
            fclose(fp);
            return false;
        }
        free(null_bytes);

        // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
        header.header64.e_shoff     = 0;
        header.header64.e_shentsize = 0;
        header.header64.e_shnum     = 0;
        header.header64.e_shstrndx  = 0;
    }

    // Write the bytes out
    fseek(fp, 0, SEEK_SET);
    if ( fwrite((char *)&header, header_size, 1, fp) != 1 )
    {
        fprintf(stderr, "Failed to overwrite header.\n");
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}
