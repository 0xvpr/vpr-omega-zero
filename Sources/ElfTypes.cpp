#include "ElfTypes.hpp"
#include "Filetypes.hpp"

#include <iostream>
#include <cstring>

void elftypes::ProcessElfx86(char* filename) {

    // Open file as binary
    FILE*       fp{nullptr};
    uint32_t     e_shoff{0};
    uint16_t    e_shentsize{0};
    uint16_t    e_shnum{0};
    uint32_t    shsize{0};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get section-header start offset
    fseek(fp, 0x20, SEEK_SET);
    if (fread(&e_shoff, sizeof(uint32_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for start offset." << std::endl;
        exit(errno);
    }

    // Get entry size
    fseek(fp, 0x2E, SEEK_SET);
    if (fread(&e_shentsize, sizeof(uint16_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for entry size." << std::endl;
        exit(errno);
    }

    // Number of entries
    fseek(fp, 0x30, SEEK_SET); // two bytes
    if (fread(&e_shnum, sizeof(uint16_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for number of entries." << std::endl;
        exit(errno);
    }

    // If file has a zeroed value, skip the file
    if ((e_shentsize * e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fclose(fp);
        return;
    }

    // Calculate total size
    shsize = e_shentsize * e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fseek(fp, e_shoff, SEEK_SET);
    if (fwrite(null_bytes, sizeof(char), shsize, fp) != shsize) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        exit(std::ferror(fp));
    }
    delete[] null_bytes;

    // Overwrite the pointers section header info
    const uint16_t shoffsets[4] = { 0x20, 0x2E, 0x30, 0x32 }; // offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    for (const auto offset : shoffsets) {
        fseek(fp, offset, SEEK_SET);
        if (offset == 0x20) {
            unsigned char bytes[4]{0};
            if (fwrite(bytes, sizeof(char), sizeof(bytes), fp) != sizeof(bytes)) {
                std::cerr << "Failed to overwrite entry size." << std::endl;
                exit(std::ferror(fp));
            }
        } else {
            unsigned char bytes[2]{0};
            if (fwrite(bytes, sizeof(char), sizeof(bytes), fp) != sizeof(bytes)) {
                std::cerr << "Failed to overwrite number of entries." << std::endl;
                exit(std::ferror(fp));
            }
        }
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}

void elftypes::ProcessElfx86_64(char* filename) {

    // Open file as binary
    FILE*       fp{nullptr};
    int64_t     e_shoff{0};
    uint16_t    e_shentsize{0};
    uint16_t    e_shnum{0};
    uint32_t    shsize{0};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get section-header start offset
    fseek(fp, 0x28, SEEK_SET);
    if (fread(&e_shoff, sizeof(int64_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for start offset." << std::endl;
        exit(errno);
    }

    // Get entry size
    fseek(fp, 0x3A, SEEK_SET);
    if (fread(&e_shentsize, sizeof(uint16_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for entry size." << std::endl;
        exit(errno);
    }

    // Number of entries
    fseek(fp, 0x3C, SEEK_SET); // two bytes
    if (fread(&e_shnum, sizeof(uint16_t), 1, fp) != 1) {
        std::cerr << "Failed to read bytes for number of entries." << std::endl;
        exit(errno);
    }

    // If file has a zeroed value, skip the file
    if ((e_shentsize * e_shnum) == 0) {
        std::cerr << "'" << filename << "' has a invalid section header entry size and/or section header number.\n"
                  << "Skipping '" << filename << "'.\n";
        fclose(fp);
        return;
    }

    // Calculate total size
    shsize = e_shentsize * e_shnum;
    auto null_bytes = new char[shsize];
    memset(null_bytes, 0, shsize);

    // Overwrite total bytes
    fseek(fp, e_shoff, SEEK_SET);
    if (fwrite(null_bytes, sizeof(char), shsize, fp) != shsize) {
        delete[] null_bytes;
        std::cerr << "Failed to overwrite section-header." << std::endl;
        exit(std::ferror(fp));
    }
    delete[] null_bytes;

    // Overwrite the pointers section header info
    const uint16_t shoffsets[4] = { 0x28, 0x3A, 0x3C, 0x3E }; // offsets for e_shoff, e_shentsize, e_shnum, and e_shstrndx
    for (const auto offset : shoffsets) {
        fseek(fp, offset, SEEK_SET);
        if (offset == 0x28) {
            unsigned char bytes[8]{0};
            if (fwrite(bytes, sizeof(char), sizeof(bytes), fp) != sizeof(bytes)) {
                std::cerr << "Failed to overwrite entry size." << std::endl;
                exit(std::ferror(fp));
            }
        } else {
            unsigned char bytes[2]{0};
            if (fwrite(bytes, sizeof(char), sizeof(bytes), fp) != sizeof(bytes)) {
                std::cerr << "Failed to overwrite number of entries." << std::endl;
                exit(std::ferror(fp));
            }
        }
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}
