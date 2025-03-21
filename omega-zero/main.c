/**
 * Project:     vpr-omega-zero
 *
 * Created by:  VPR
 * Created:     March 9th, 2022
 *
 * Updated by:  March 9th, 2022
 * Updated:     March 15th, 2025
 *
 * Description: Inspired by yellobytes's 'zeroSection2.py'
 *              https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks
 *
 *              Omega Zero aims to provide a tool for the stripping of the
 *              section-header information of x86 and x86_64 ELF and PE32 binaries.
 *
 * License: MIT
**/

#include "filetypes.h"
#include "util.h"
#include "pe32.h"
#include "elf.h"

#include <stdlib.h>
#include <string.h>

static const char* filenames[4096];
static size_t n_filenames;
static flags_t flags = { .zero_all = 1 };

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        __usage_error(argv[0], "insufficient arguments");
    }

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-' && argv[i][1])
        {
            for (int j = 1; argv[i][j]; ++j)
            {
                switch (argv[i][j])
                {
                    case 'H': flags.zero_headers           = 1; break;
                    case 'o': flags.zero_optional_headers  = 1; break;
                    case 's': flags.zero_section_headers   = 1; break;
                    case 'a': flags.zero_all               = 1; break;
                    case 'h': __usage_error(argv[0], "display help"); break;
                    case '-':
                    {
                        if (strncmp((argv[i]+j), "-help", sizeof("-help")) == 0)
                        {
                            __usage_error(argv[0], "display help");
                        }
                        else if (strncmp((argv[i]+j), "-headers", sizeof("-headers")) == 0)
                        {
                            flags.zero_headers = 1;
                        }
                        else if (strncmp((argv[i]+j), "-optional-headers", sizeof("-optional-headers")) == 0)
                        {
                            flags.zero_headers = 1;
                        }
                        else if (strncmp((argv[i]+j), "-section-headers", sizeof("-section-headers")) == 0)
                        {
                            flags.zero_headers = 1;
                        }
                        else if (strncmp((argv[i]+j), "-all", sizeof("-all")) == 0)
                        {
                            flags.zero_headers = 1;
                        }
                        break;
                    }
                    default:  fprintf(stderr, "unknown option: %c\n", argv[i][j]); break;
                }
            }
        }
        else
        {
            filenames[n_filenames] = argv[i];
            ++n_filenames;
        }
    }

    // Default to zero_all if none are set
    if ( !(flags.zero_headers | flags.zero_section_headers | flags.zero_optional_headers) )
    {
        flags.zero_all = 1;
    }

    if (!n_filenames)
    {
        __usage_error(argv[0], "no files supplied");
    }

    for (size_t i = 0; i < n_filenames; ++i)
    {
        const char* const filename = filenames[i];
        fprintf(stderr, "Processing '%s'...\n", filename);

        FILE* fp = 0;
        if ( !(fp = fopen(filename, "rb")) )
        {
            fprintf(stderr, "Failed to open '%s'.\n", filename);
            fprintf(stdout, "Skipping '%s'...\n", filename);
            continue;
        }
        fclose(fp);

        bool bSuccess = false;
        enum filetype_t filetype = determine_filetype(filename);
        switch (filetype)
        {
            case unsupported:
            {
                fprintf(stderr, "Filetype not supported.\n");
                fprintf(stdout, "Skipping '%s'...\n", filename);
                continue;
            }
            case pe_x86:
            {
                fputs("PE32 detected\n", stdout);
                bSuccess = process_pe32(filename, &flags, pe_x86);
                break;
            }
            case pe_x86_64:
            {
                fputs("PE32+(x86_64) detected\n", stdout);
                bSuccess = process_pe32(filename, &flags, pe_x86_64);
                break;
            }
            case elf_x86:
            {
                fputs("ELF x86 detected\n", stdout);
                bSuccess = process_elf(filename, &flags, elf_x86);
                break;
            }
            case elf_x86_64:
            {
                fputs("ELF x86_64 detected\n", stdout);
                bSuccess = process_elf(filename, &flags, elf_x86_64);
                break;
            }
        }

        if (bSuccess) {
            fprintf(stdout, "'%s' was successfully processed.\n", filename);
        } else {
            fprintf(stdout, "Failed to process '%s'.\n", filename);
        }

    }

    return 0;
}
