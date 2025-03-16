#include "util.h"

#include "version.h"

#include <stdlib.h>
#include <stdio.h>

void __usage_error(const char* restrict argv_0, const char* restrict error_message)
{
    fprintf(stderr,
        "Error message: %s.\n"
        "\n"
        "Usage:\n"
        "  %s [<optional_arguments>] <path/to/executable-1> <path/to/executable-2> \n"
        "\n"
        "Optional arguments:\n"
        "  -a,                Enable all flags. (default option)\n"
        "  --all\n"
        "  -o,                Zero all optional headers.\n"
        "  --optional-headers\n"
        "  -s,                Zero all section headers.\n"
        "  --section-headers\n"
        "  -H                 Zero all headers.\n"
        "  -headers\n"
        "  -h,                Display help.\n"
        "  --help\n"
        "\n"
        "Examples:\n"
        "  %s path/to/executable\n"
        "  %s -sH path/to/executable\n"
        "\n"
        "Version:\n"
        "  %d.%d.%d\n"
        "\n"
        "Author:\n"
        "  VPR\n",
        error_message,
        argv_0,
        argv_0,
        argv_0,
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH
    );

    exit(1);
}
