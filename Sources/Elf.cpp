#include "Elf.hpp"

#include "Filetypes.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

using elf::ElfHeader32;
using elf::ElfHeader64;

[[nodiscard]]
bool elf::ProcessElf32(char* filename) {

    std::fstream fs;
    ElfHeader32 header;

    // Open target file
    fs.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs.is_open()) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        return false;
    }

    // Get header information
    fs.seekg(0, std::ios::beg);
    fs.read((char *)&header, sizeof(header));
    if (fs.fail()) {
        std::cerr << "Failed to read bytes for elf header." << std::endl;
        fs.close();
        return false;
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fs.close();
        return false;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fs.seekg(header.e_shoff, std::ios::beg);
    fs.write(null_bytes, static_cast<long>(shsize));
    if (fs.fail()) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        fs.close();
        return false;
    }
    delete[] null_bytes;

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fs.seekg(0, std::ios::beg);
    fs.write((char *)&header, sizeof(header));
    if (fs.fail()) {
        std::cerr << "Failed to overwrite header." << std::endl;
        fs.close();
        return false;
    }

    fs.close();
    return true;
}

[[nodiscard]]
bool elf::ProcessElf64(char* filename) {

    std::fstream fs;
    ElfHeader64 header;

    // Open target file
    fs.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs.is_open()) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        return false;
    }

    // Get header information
    fs.seekg(0, std::ios::beg);
    fs.read((char *)&header, sizeof(header));
    if (fs.fail()) {
        std::cerr << "Failed to read bytes for elf header." << std::endl;
        fs.close();
        return false;
    }
    
    // If file has a zeroed value, skip the file
    if ((header.e_shentsize * header.e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fs.close();
        return false;
    }

    // Calculate total size
    size_t shsize = header.e_shentsize * header.e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fs.seekg((long)header.e_shoff, std::ios::beg);
    fs.write(null_bytes, static_cast<long>(shsize));
    if (fs.fail()) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        fs.close();
        return false;
    }
    delete[] null_bytes;

    // Set offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    header.e_shoff     = 0;
    header.e_shentsize = 0;
    header.e_shnum     = 0;
    header.e_shstrndx  = 0;

    // Write the bytes out
    fs.seekg(0, std::ios::beg);
    fs.write((char *)&header, sizeof(header));
    if (fs.fail()) {
        std::cerr << "Failed to overwrite header." << std::endl;
        fs.close();
        return false;
    }

    fs.close();
    return true;
}
