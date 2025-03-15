#include "util.h"

#include <stdlib.h>

void __usage_error(const char* restrict argv_0, const char* restrict message) {
    (void)argv_0;
    (void)message;
    /*std::cerr << "Usage error " << error_code << ": " << [&error_code]() -> std::string {*/
                  /*switch (error_code) {*/
                      /*case -1: { return "no arguments supplied."; }*/
                      /*default: { return "unknown error."; }*/
                  /*}*/
              /*}() << "\n"*/
              /*<< "\n"*/
              /*<< "example usage:\n"*/
              /*<< "  " << argv_0 << " path/to/executable"*/
              /*<< std::endl;*/

    exit(1);
}
