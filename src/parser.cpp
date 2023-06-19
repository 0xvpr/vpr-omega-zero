#include "parser.hpp"

static
file_arr_t SetFilenames(int argc, char** argv) {

    if (argc < 2) {
        return { };
    }

    std::string program_name(argv[0]);

    std::vector<std::string> arguments;
    for (int i = 1; i < argc; i++) {
        std::string argument(argv[i]);

        if (argument == program_name) {
            continue;
        } else if (argument[0] == '-') {
            continue;
        }

        arguments.push_back(argument);
    }

    return arguments;

}

static
uint32_t SetOperations(int argc, char** argv) {
    (void)argc;
    (void)argv;
    return 0;
}

parser::CommandLine::CommandLine(int argc, char** argv)
    : operations(SetOperations(argc, argv))
    , filenames(SetFilenames(argc, argv))
{
}

parser::CommandLine::~CommandLine()
{
}

uint32_t parser::CommandLine::Operations() const { return operations; }
const std::vector<std::string> parser::CommandLine::Filenames() const { return filenames; }

//parser::CommandLine::GetOperations(int argc, char** argv);
