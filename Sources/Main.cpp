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

#include "Filetypes.hpp"   // namespace filetypes
#include "Util.hpp"        // __usage_error
#include "Pe32.hpp"        // namespace pe32
#include "Elf.hpp"         // namespace elf

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
            return ifs.fail();
        }

        auto filetype = filetypes::DetermineFiletype(ifs);
        switch (filetype)
        {
            case filetypes::unsupported:
            {
                std::cout << "Filetype not supported." << " " << filetype << "\n"
                          << "Skipping '" << filename << "'." << std::endl;
                break;
            }
            case filetypes::pe_x86:
            {
                std::cout << "PE32" << std::endl;
                pe32::ProcessPe32(filename);
                break;
            }
            case filetypes::pe_x86_64:
            {
                std::cout << "PE32+ (x86_64)" << std::endl;
                pe32::ProcessPe64(filename);
                break;
            }
            case filetypes::elf_x86:
            {
                std::cout << "ELF x86" << std::endl;
                elf::ProcessElf32(filename);
                break;
            }
            case filetypes::elf_x86_64:
            {
                std::cout << "ELF x86_64" << std::endl;
                elf::ProcessElf64(filename);
                break;
            }
        }
    }

    return 0;

}
