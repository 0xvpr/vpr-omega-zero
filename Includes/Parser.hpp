#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <vector>
#include <string>

typedef std::vector<std::string> file_arr_t;

namespace parser {

    class CommandLine;

} // namespace parser

class parser::CommandLine {
private:
    const uint32_t operations;
    const file_arr_t filenames;
public:
    CommandLine() = delete;
    CommandLine(const CommandLine& other) = delete;
    CommandLine(int argc, char** argv);
    ~CommandLine();
public:
    uint32_t Operations() const;
    const file_arr_t Filenames() const;
};

#endif // PARSER_HEADER
