#include "util.hpp"

void __usage_error(char* argv_0, int error_code) {
    std::cerr << "Usage error " << error_code << ": " << [&error_code]() -> std::string {
                  switch (error_code) {
                      case -1: { return "no arguments supplied."; }
                      default: { return "unknown error."; }
                  }
              }() << "\n"
              << "\n"
              << "example usage:\n"
              << "  " << argv_0 << " path/to/executable"
              << std::endl;

    exit(error_code);
}
