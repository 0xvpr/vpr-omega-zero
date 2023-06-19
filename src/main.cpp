/**
 * Project:    vpr-omega-zero
 *
 * Creator:    VPR
 * Created:    March 9th, 2022
 * Updated:    March 11th, 2022
 *
 * Description:
 *     Inspired by yellobytes's 'zeroSection2.py'
 *     https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks
 *
 *     Omega Zero aims to provide a tool for the stripping of the
 *     section-header information of x86 and x86_64 ELF and PE32 binaries.
**/

#include "filetypes.hpp"   // namespace filetypes
#include "parser.hpp"      // namespace parser
#include "util.hpp"        // __usage_error
#include "pe32.hpp"        // namespace pe32
#include "elf.hpp"         // namespace elf

#include <filesystem>
#include <iostream>
#include <fstream>

#define ERR_NO_ARGS (int)0xFFFFFFFF

int main(int argc, char** argv) {

    if (argc < 2) {
        __usage_error(argv[0], ERR_NO_ARGS);
    }

    auto cl = parser::CommandLine(argc, argv);
    for (const auto& filename : cl.Filenames()) {

        std::cout << "Processing '" << filename << "'..." << std::endl;

        if (!std::filesystem::exists(filename)) {
            std::cerr << "'" << filename << "' does not exist." << std::endl;
            std::cout << "Skipping '" << filename << "'...\n" << std::endl;
            continue;
        } else if (!std::filesystem::is_regular_file(filename) || std::filesystem::is_directory(filename)) {
            std::cerr << "'" << filename << "' is not a regular file." << std::endl;
            std::cout << "Skipping '" << filename << "'...\n" << std::endl;
            continue;
        }

        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open '" << filename << "'.\n" << std::endl;
            std::cout << "Skipping '" << filename << "'...\n" << std::endl;
            continue;
        }

        bool bSuccess = false;
        auto raw_filename = const_cast<char *>(filename.c_str());
        auto filetype = filetypes::DetermineFiletype(ifs);
        switch (filetype)
        {
            case filetypes::unsupported:
            {
                std::cerr << "Filetype not supported." << " " << filetype << std::endl;
                std::cout << "Skipping '" << filename << "'...\n" << std::endl;
                continue;
            }
            case filetypes::pe_x86:
            {
                std::cout << "PE32 detected\n";
                bSuccess = pe32::ProcessPe32(raw_filename);
                break;
            }
            case filetypes::pe_x86_64:
            {
                std::cout << "PE32+(x86_64) detected\n";
                bSuccess = pe32::ProcessPe64(raw_filename);
                break;
            }
            case filetypes::elf_x86:
            {
                std::cout << "ELF x86 detected\n";
                bSuccess = elf::ProcessElf32(raw_filename);
                break;
            }
            case filetypes::elf_x86_64:
            {
                std::cout << "ELF x86_64 detected\n";
                bSuccess = elf::ProcessElf64(raw_filename);
                break;
            }
        }

        if (bSuccess) {
            std::cout << "'" << filename << "' successfully processed.\n" << std::endl;
        } else {
            std::cout << "failed to process'" << filename << "'.\n" << std::endl;
        }

    }

    return 0;

}
