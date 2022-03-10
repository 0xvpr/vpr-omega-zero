#ifndef ELF_TYPES_HEADER
#define ELF_TYPES_HEADER

namespace elftypes {


    /**
     * Perform scraping of 32 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElfx86(char*);

    /**
     * Perform scraping of 64 bit ELF binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessElfx86_64(char*);

}

#endif // ELF_TYPES_HEADER
