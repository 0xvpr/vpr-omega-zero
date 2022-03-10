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

#include "Filetypes.hpp"   // namespace filetype
#include "PE32Types.hpp"   // namespace pe32types
#include "ElfTypes.hpp"    // namespace elftypes
#include "Util.hpp"        // __usage_error

#include <filesystem>
#include <iostream>
#include <fstream>

#define ERR_FILE_NOT_SUPPORTED 0xFF
#define ERR_NO_ARGS            0xFF
#define ERR_FILE_DNE           0x01

int main(int argc, char** argv) {

    if (!(argc-1)) {
        __usage_error(argv[0], ERR_NO_ARGS);
    }

    for (int i = 1; i < argc; i++) {

        auto filename = argv[i];
        std::cout << "Processing '" << filename << "'..." << std::endl;

        if (!std::filesystem::is_regular_file(filename)) {
            __usage_error(argv[0], ERR_FILE_DNE);
        }

        std::ifstream ifs(argv[i]);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open '" << filename << "'." << std::endl;
            return 2;
        }

        auto filetype = elftypes::DetermineFiletype(ifs);
        switch (filetype)
        {
            case filetype::unsupported:
            {
                std::cout << "Filetype not supported." << std::endl;
                break;
            }
            case filetype::pe_x86:
            {
                break;
            }
            case filetype::pe_x86_64:
            {
                std::cout << "PE32 Not yet supported." << std::endl;
                break;
            }
            case filetype::elf_x86:
            {
                elftypes::ProcessElfx86(filename);
                break;
            }
            case filetype::elf_x86_64:
            {
                elftypes::ProcessElfx86_64(filename);
                break;
            }
        }
    }

    return 0;

}
