#include "elf.h"

#include "filetypes.h"

#include <string.h>
#include <stdlib.h>

bool process_elf32(const char* restrict filename, flags_ptr_t flags)
{
    (void)flags;

    FILE* fp = 0;
    ElfHeader32 header = { 0 };

    // Open target file
    if ( !(fp = fopen(filename, "rb+")) )
    {
        fprintf(stderr, "Failed to open '%s' for reading.\n", filename);
        return false;
    }

    // Get header information
    fseek(fp, 0, SEEK_SET);
    unsigned long bytes_read = fread((unsigned char *)&header, sizeof(header), 1, fp);
    if (bytes_read != 1) 
    {
        fprintf(stderr, "Failed to read bytes for elf header.\n");
        fclose(fp);
        return false;
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        fprintf(stderr, "'%s' has a invalid section header entry size and/or section header number.\n"
                        "Skipping '%s'.\n", filename, filename);
        fclose(fp);
        return false;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    unsigned char* null_bytes = (unsigned char *)calloc(1, sizeof(unsigned char) * shsize);
    if (!null_bytes)
    {
        fprintf(stderr, "Failed to allocate null-bytes.\n");
        fclose(fp);
        return false;
    }

    // Overwrite total bytes
    fseek(fp, header.e_shoff, SEEK_SET);
    if ( fwrite(null_bytes, (unsigned long)(shsize), 1, fp) != 1 )
    {
        free(null_bytes);
        fprintf(stderr, "Failed to overwrite section-header.\n");
        fclose(fp);
        return false;
    }
    free(null_bytes);

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fseek(fp, 0, SEEK_SET);
    if ( fwrite((char *)&header, sizeof(header), 1, fp) != 1 )
    {
        fprintf(stderr, "Failed to overwrite header.\n");
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

bool process_elf64(const char* restrict filename, flags_ptr_t flags)
{
    (void)flags;

    FILE* fp = 0;
    ElfHeader64 header = { 0 };

    // Open target file
    if ( !(fp = fopen(filename, "rb+")) )
    {
        fprintf(stderr, "Failed to open '%s' for reading.\n", filename);
        return false;
    }

    // Get header information
    fseek(fp, 0, SEEK_SET);
    unsigned long bytes_read = fread((unsigned char *)&header, sizeof(header), 1, fp);
    if (bytes_read != 1) 
    {
        fprintf(stderr, "Failed to read bytes for elf header.\n");
        fclose(fp);
        return false;
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        fprintf(stderr, "'%s' has a invalid section header entry size and/or section header number.\n"
                        "Skipping '%s'.\n", filename, filename);
        fclose(fp);
        return false;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    unsigned char* null_bytes = (unsigned char *)calloc(1, sizeof(unsigned char) * shsize);
    if (!null_bytes)
    {
        fprintf(stderr, "Failed to allocate null-bytes.\n");
        fclose(fp);
        return false;
    }

    // Overwrite total bytes
    fseek(fp, (long)header.e_shoff, SEEK_SET);
    if ( fwrite(null_bytes, (unsigned long)(shsize), 1, fp) != 1 )
    {
        free(null_bytes);
        fprintf(stderr, "Failed to overwrite section-header.\n");
        fclose(fp);
        return false;
    }
    free(null_bytes);

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fseek(fp, 0, SEEK_SET);
    if ( fwrite((char *)&header, sizeof(header), 1, fp) != 1 )
    {
        fprintf(stderr, "Failed to overwrite header.\n");
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}
