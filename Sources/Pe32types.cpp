#include "Pe32Types.hpp"

#include <iostream>
#include <cstring>

using pe32types::Pe32OptionalHeader;
using pe32types::Pe32Header;
using pe32types::MsDosStub;

void pe32types::ProcessPe32x86(char* filename) {

    FILE*               fp{nullptr};
    Pe32Header          header{};
    Pe32OptionalHeader  optional_header{};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ((fread(&header, sizeof(Pe32Header), 1, fp)) != 1) {
        std::cerr << "Failed to read header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    // Get optional header
    fseek(fp, sizeof(Pe32Header) + sizeof(MsDosStub), SEEK_SET);
    if ((fread(&optional_header, sizeof(Pe32OptionalHeader), 1, fp)) != 1) {
        std::cerr << "Failed to read optional header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    /* Clear header */
    //header.mMagic                              = 0;  // NOPE
    //header.mMachine                            = 0;  // NOPE
    header.mTimeDateStamp                        = 0;  // OK
    //header.mNumberOfSymbols                    = 0;  // NOPE
    //header.mCharacteristics                    = 0;  // NOPE
    //header.mNumberOfSections                   = 0;  // NOPE
    //header.mSizeOfOptionalHeader               = 0;  // NOPE
    header.mPointerToSymbolTable                 = 0;  // OK

    /* Clear Optional Header */
    //optional_header.mMagic                     = 0;  // NOPE
    optional_header.mMajorLinkerVersion          = 0;  // OK
    optional_header.mMinorLinkerVersion          = 0;  // OK
    optional_header.mSizeOfCode                  = 0;  // OK
    optional_header.mSizeOfInitializedData       = 0;  // OK
    optional_header.mSizeOfUninitializedData     = 0;  // OK
    //optional_header.mAddressOfEntryPoint       = 0;  // NOPE
    optional_header.mBaseOfCode                  = 0;  // OK
    optional_header.mBaseOfData                  = 0;  // OK
    //optional_header.mImageBase                 = 0;  // FUCK NO
    //optional_header.mSectionAlignment          = 0;  // NOPE
    //optional_header.mFileAlignment             = 0;  // NO
    optional_header.mMajorOperatingSystemVersion = 0;  // OK
    optional_header.mMinorOperatingSystemVersion = 0;  // OK
    optional_header.mMajorImageVersion           = 0;  // OK
    optional_header.mMinorImageVersion           = 0;  // OK
    //optional_header.mMajorSubsystemVersion     = 0;  // needs specific value
    optional_header.mMinorSubsystemVersion       = 0;  // OK
    optional_header.mWin32VersionValue           = 0;  // OK
    //optional_header.mSizeOfImage               = 0;  // NOPE
    //optional_header.mSizeOfHeaders             = 0;  // NOPE
    optional_header.mCheckSum                    = 0;  // OK
    //optional_header.mSubsystem                 = 0;  // nah
    optional_header.mDllCharacteristics          = 0;  // hmmmm  maybe
    optional_header.mSizeOfStackReserve          = 0;  // OK
    optional_header.mSizeOfStackCommit           = 0;  // OK
    optional_header.mSizeOfHeapReserve           = 0;  // OK
    optional_header.mSizeOfHeapCommit            = 0;  // OK
    optional_header.mLoaderFlags                 = 0;  // OK
    //optional_header.mNumberOfRvaAndSizes       = 0;  // Absolutely the fuck not

    // Set PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ((fwrite(&header, sizeof(Pe32Header), 1, fp)) != 1) {
        std::cerr << "Failed to write header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    // Set optional header
    fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
    if ((fwrite(&optional_header, sizeof(Pe32OptionalHeader), 1, fp)) != 1) {
        std::cerr << "Failed to write header of '" << filename << "'." << std::endl;
        exit(errno);
    }
    
    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}

void pe32types::ProcessPe32x86_64(char* filename) {

    FILE*               fp{nullptr};
    Pe32Header          header{};
    Pe32OptionalHeader  optional_header{};

    // Open target file
    if (!(fp = fopen(filename, "rb+"))) {
        std::cerr << "Failed to open '" << filename << "' for reading." << std::endl;
        exit(errno);
    }

    // Get PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ((fread(&header, sizeof(Pe32Header), 1, fp)) != 1) {
        std::cerr << "Failed to read header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    // Get optional header
    fseek(fp, sizeof(Pe32Header) + sizeof(MsDosStub), SEEK_SET);
    if ((fread(&optional_header, sizeof(Pe32OptionalHeader), 1, fp)) != 1) {
        std::cerr << "Failed to read optional header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    /* Clear header */
    //header.mMagic                              = 0;  // NOPE
    //header.mMachine                            = 0;  // NOPE
    header.mTimeDateStamp                        = 0;  // OK
    //header.mNumberOfSymbols                    = 0;  // NOPE
    //header.mCharacteristics                    = 0;  // NOPE
    //header.mNumberOfSections                   = 0;  // NOPE
    //header.mSizeOfOptionalHeader               = 0;  // NOPE
    header.mPointerToSymbolTable                 = 0;  // OK

    /* Clear Optional Header */
    //optional_header.mMagic                     = 0;  // NOPE
    optional_header.mMajorLinkerVersion          = 0;  // OK
    optional_header.mMinorLinkerVersion          = 0;  // OK
    optional_header.mSizeOfCode                  = 0;  // OK
    optional_header.mSizeOfInitializedData       = 0;  // OK
    optional_header.mSizeOfUninitializedData     = 0;  // OK
    //optional_header.mAddressOfEntryPoint       = 0;  // NOPE
    optional_header.mBaseOfCode                  = 0;  // OK
    optional_header.mBaseOfData                  = 0;  // OK
    //optional_header.mImageBase                 = 0;  // FUCK NO
    //optional_header.mSectionAlignment          = 0;  // NOPE
    //optional_header.mFileAlignment             = 0;  // NO
    optional_header.mMajorOperatingSystemVersion = 0;  // OK
    optional_header.mMinorOperatingSystemVersion = 0;  // OK
    optional_header.mMajorImageVersion           = 0;  // OK
    optional_header.mMinorImageVersion           = 0;  // OK
    //optional_header.mMajorSubsystemVersion     = 0;  // needs specific value
    optional_header.mMinorSubsystemVersion       = 0;  // OK
    optional_header.mWin32VersionValue           = 0;  // OK
    //optional_header.mSizeOfImage               = 0;  // NOPE
    //optional_header.mSizeOfHeaders             = 0;  // NOPE
    optional_header.mCheckSum                    = 0;  // OK
    //optional_header.mSubsystem                 = 0;  // nah
    optional_header.mDllCharacteristics          = 0;  // hmmmm  maybe
    optional_header.mSizeOfStackReserve          = 0;  // OK
    optional_header.mSizeOfStackCommit           = 0;  // OK
    optional_header.mSizeOfHeapReserve           = 0;  // OK
    optional_header.mSizeOfHeapCommit            = 0;  // OK
    optional_header.mLoaderFlags                 = 0;  // OK
    //optional_header.mNumberOfRvaAndSizes       = 0;  // Absolutely the fuck not

    // Set PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ((fwrite(&header, sizeof(Pe32Header), 1, fp)) != 1) {
        std::cerr << "Failed to write header of '" << filename << "'." << std::endl;
        exit(errno);
    }

    // Set optional header
    fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
    if ((fwrite(&optional_header, sizeof(Pe32OptionalHeader), 1, fp)) != 1) {
        std::cerr << "Failed to write header of '" << filename << "'." << std::endl;
        exit(errno);
    }
    
    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}
