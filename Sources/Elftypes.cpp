#include "ElfTypes.hpp"
#include "Filetypes.hpp"

#include <iostream>
#include <cstring>

using elftypes::ElfHeader32;
using elftypes::ElfHeader64;

void elftypes::ProcessElfx86(char* filename) {

    FILE*       fp{nullptr};
    ElfHeader32 header{};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get header information
    fseek(fp, 0, SEEK_SET);
    if (fread(&header, sizeof(ElfHeader32), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for elf header." << std::endl;
        exit(errno);
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fclose(fp);
        return;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fseek(fp, header.e_shoff, SEEK_SET);
    if (fwrite(null_bytes, sizeof(char), shsize, fp) != shsize) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        exit(std::ferror(fp));
    }
    delete[] null_bytes;

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fseek(fp, 0, SEEK_SET);
    if (fwrite(&header, sizeof(ElfHeader32), 1, fp) != 1) {
        std::cerr << "Failed to overwrite header." << std::endl;
        exit(std::ferror(fp));
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}

void elftypes::ProcessElfx86_64(char* filename) {

    FILE*       fp{nullptr};
    ElfHeader64 header{};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get header information
    fseek(fp, 0, SEEK_SET);
    if (fread(&header, sizeof(ElfHeader64), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for elf header." << std::endl;
        exit(errno);
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fclose(fp);
        return;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fseek(fp, (uint32_t)header.e_shoff, SEEK_SET);
    if (fwrite(null_bytes, sizeof(char), shsize, fp) != shsize) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        exit(std::ferror(fp));
    }
    delete[] null_bytes;

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fseek(fp, 0, SEEK_SET);
    if (fwrite(&header, sizeof(ElfHeader64), 1, fp) != 1) {
        std::cerr << "Failed to overwrite header." << std::endl;
        exit(std::ferror(fp));
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}
