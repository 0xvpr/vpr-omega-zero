/**
 * Creator: VPR
 * Created: March 9th, 2022
 * Updated: March 9th, 2022
 *
 * Description:
 *     Inspired by yellobytes's 'zeroSection2.py'
 *     https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks
 *
 *     This project aim's to provide a tool for the stripping of the
 *     section-header information of ELF and PE32 executables.
**/

#include "Util.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define ERR_FILE_NOT_SUPPORTED 0xFF
#define ERR_NO_ARGS            0xFF
#define ERR_FILE_DNE           0x01

namespace filetype {
    enum {
        unsupported,   // 0
        pe_x86,        // 1
        pe_x86_64,     // 2
        elf_x86,       // 3
        elf_x86_64     // 4
    };
}

[[nodiscard]]
static uint16_t DetermineFiletype(std::ifstream& ifs) {

    if (ifs.good()) {
        char cbuffer[4]{0};
        
        ifs.read(cbuffer, sizeof(cbuffer));
        const std::string buffer(cbuffer);

        if (buffer.starts_with("MZ")) {
            ifs.close();
            return filetype::pe_x86_64;
        } else if (buffer.find("ELF") != buffer.npos) {
            ifs.close();
            return filetype::elf_x86_64;
        }
    }

    ifs.close();
    return filetype::unsupported;
}

int main(int argc, char** argv) {

    if (!(argc-1)) {
        __usage_error(argv[0], ERR_NO_ARGS);
    }

    for (int i = 1; i < argc; i++) {
        if (!std::filesystem::is_regular_file(argv[i])) {
            __usage_error(argv[0], ERR_FILE_DNE);
        }

        std::ifstream ifs(argv[i]);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open '" << argv[i] << "'." << std::endl;
            return 2;
        }
        
        auto filetype = DetermineFiletype(ifs);
        switch (filetype)
        {
            case filetype::unsupported:
            {
                std::cout << "Filetype not supported." << std::endl;
                break;
            }
            case filetype::pe_x86:
            case filetype::pe_x86_64:
            {
                std::cout << "PE32 Not yet supported." << std::endl;
                break;
            }
            case filetype::elf_x86:
            case filetype::elf_x86_64:
            {
                std::cout << "Processing: " << argv[i] << "..." << std::endl;

                // Open file as binary
                FILE*       fp{nullptr};
                uint16_t    start_offset{0};
                uint16_t    entry_size{0};
                uint16_t    n_entries{0};
                uint32_t    size{0};

                // Open target file
                if (!(fp = fopen(argv[1], "rb+"))) {
                    std::cerr << "Failed to open '" << argv[1] << "' for reading." << std::endl;
                    return errno;
                }

                // Get section-header start offset
                fseek(fp, 0x20, SEEK_SET);
                if (!fread(&start_offset, sizeof(start_offset), 1, fp)) {
                    std::cerr << "Failed to read bytes for start offset." << std::endl;
                    return errno;
                }

                // Get entry size
                fseek(fp, 0x2E, SEEK_SET); // two bytes
                if (!fread(&entry_size, sizeof(entry_size), 1, fp)) {
                    std::cerr << "Failed to read bytes for entry size." << std::endl;
                    return errno;
                }

                // Number of entries
                fseek(fp, 0x30, SEEK_SET); // two bytes
                if (!fread(&n_entries, sizeof(n_entries), 1, fp)) {
                    std::cerr << "Failed to read bytes for number of entries." << std::endl;
                    return errno;
                }

                // Calculate total size
                size = entry_size * n_entries;
                auto null_bytes = new char[size];
                memset(null_bytes, 0, size);

                // Overwrite total bytes
                fseek(fp, start_offset, SEEK_SET);
                if (fwrite(null_bytes, sizeof(char), size, fp)) {
                    delete[] null_bytes;
                    std::cerr << "Failed to overwrite section-header." << std::endl;
                    return errno;
                }

                // Overwrite the pointers section header info
                const uint16_t offsets[4] = { 0x20, 0x2E, 0x30, 0x32 };
                for (const auto offset : offsets) {
                    fseek(fp, offset, SEEK_SET);
                    if (offset == 0x20) {
                        if (!fwrite(null_bytes, sizeof(char), 4, fp)) {
                            delete[] null_bytes;
                            std::cerr << "Failed to overwrite entry size." << std::endl;
                            return errno;
                        }
                    } else {
                        if (!fwrite(null_bytes, sizeof(char), 2, fp)) {
                            delete[] null_bytes;
                            std::cerr << "Failed to overwrite number of entries." << std::endl;
                            return errno;
                        }
                    }
                }

                std::cout << argv[i] << " Successfully processed." << std::endl;

                delete[] null_bytes;
                fclose(fp);
                break;
            }
        }
    }

    return 0;

}
