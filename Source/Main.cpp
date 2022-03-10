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

#define FILE_TYPE_PE     0x00000001
#define FILE_TYPE_ELF    0x00000002

#define ERR_NO_ARGS (int)0xFFFFFFFF
#define ERR_FILE_DNE     0x00000001

[[nodiscard]]
static int DetermineFiletype(std::ifstream& ifs) {

    if (ifs.good()) {
        char cbuffer[4]{0};
        
        ifs.read(cbuffer, sizeof(cbuffer));
        const std::string buffer(cbuffer);

        if (buffer.starts_with("MZ")) {
            return 1;
        } else if (buffer.find("ELF") != buffer.npos) {
            return 2;
        }
    }

    return 0;
}

[[nodiscard]]
int main(int argc, char** argv) {

    if (!(argc-1)) {
        __usage_error(argv[0], ERR_NO_ARGS);
    }

    if (!std::filesystem::is_regular_file(argv[1])) {
        __usage_error(argv[0], ERR_FILE_DNE);
    }

    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        return 2; // failed to open file
    }
    
    int filetype = DetermineFiletype(ifs);
    ifs.close();

    switch (filetype)
    {
        case 0:
        {
            std::cout << "Filetype not supported." << std::endl;
            return -1;
        }
        case 1:
        {
            std::cout << "PE32 Not yet supported." << std::endl;
            return -1;
        }
        case 2:
        {
            std::cout << "ELF detected.\n" << std::endl;

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
            fseek(fp, 32, SEEK_SET);
            if (!fread(&start_offset, sizeof(start_offset), 1, fp)) {
                std::cerr << "Failed to read bytes for start offset." << std::endl;
                return errno;
            }

            // Get entry size
            fseek(fp, 46, SEEK_SET); // two bytes
            if (!fread(&entry_size, sizeof(entry_size), 1, fp)) {
                std::cerr << "Failed to read bytes for entry size." << std::endl;
                return errno;
            }

            // Number of entries
            fseek(fp, 48, SEEK_SET); // two bytes
            if (!fread(&n_entries, sizeof(n_entries), 1, fp)) {
                std::cerr << "Failed to read bytes for number of entries." << std::endl;
                return errno;
            }

            // Calculate total size
            size = entry_size * n_entries;
            auto null_bytes = new char[size];
            memset(null_bytes, 0, size);

//#ifdef NDEBUG
            //std::cout << "Start:\t\t"    << start_offset << "\n"
                      //<< "Entry size:\t" << entry_size   << "\n"
                      //<< "# Entries:\t"  << n_entries    << "\n"
                      //<< std::endl;
//#endif // NDEBUG

            // Overwrite total bytes
            fseek(fp, start_offset, SEEK_SET);
            fwrite(null_bytes, sizeof(char), size, fp);

            // Overwrite the pointers section header info
            const uint16_t offsets[4] = { 0x20, 0x2e, 0x30, 0x32 };
            for (const auto offset : offsets) {
                fseek(fp, offset, SEEK_SET);
                if (offset == 0x20) {
                    fwrite(null_bytes, sizeof(char), 4, fp);
                } else {
                    fwrite(null_bytes, sizeof(char), 2, fp);
                }
            }

            delete[] null_bytes;
            fclose(fp);
            return 0;
        }
        default:
            break;
    }

    if (ifs.is_open()) {
        ifs.close();
    }
    return 0;

}
