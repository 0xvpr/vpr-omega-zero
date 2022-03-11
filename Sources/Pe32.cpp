#include "Pe32.hpp"

#include <iostream>
#include <cstring>

void pe32::ProcessPe32(char* filename) {

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
    //optional_header.mWin32VersionValue         = 0;  // OK but probably not
    //optional_header.mSizeOfImage               = 0;  // NOPE
    //optional_header.mSizeOfHeaders             = 0;  // NOPE
    optional_header.mCheckSum                    = 0;  // OK
    //optional_header.mSubsystem                 = 0;  // nah
    //optional_header.mDllCharacteristics        = 0;  // hmmmm... maybe but probably not
    optional_header.mSizeOfStackReserve          = 0;  // OK
    optional_header.mSizeOfStackCommit           = 0;  // OK
    optional_header.mSizeOfHeapReserve           = 0;  // OK
    optional_header.mSizeOfHeapCommit            = 0;  // OK
    optional_header.mLoaderFlags                 = 0;  // OK but probably not
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
    
    // Zero out each section header
    for (unsigned i = 0; i < header.mNumberOfSections; i++) {
        Pe32SectionHeader section_header;
        long offset = sizeof(MsDosStub) + sizeof(Pe32Header) +
            header.mSizeOfOptionalHeader + i * sizeof(Pe32SectionHeader);

        // Get section header
        fseek(fp, offset, SEEK_SET);
        if ((fread(&section_header, sizeof(Pe32SectionHeader), 1, fp)) != 1) {
            std::cerr << "Failed to read section header of '" << filename << "'." << std::endl;
            exit(errno);
        }

        // Clear entries of section header
        memset(section_header.mName, 0, 8);          // yes....?
        //section_header.mVirtualSize          = 0;  // NOPE
        //section_header.mVirtualAddress       = 0;  // NOPE
        //section_header.mSizeOfRawData        = 0;  // NOPE
        //section_header.mPointerToRawData     = 0;  // NOPE
        //section_header.mPointerToRelocations = 0;  // maybe
        //section_header.mPointerToLinenumbers = 0;  // maybe
        //section_header.mNumberOfRelocations  = 0;  // maybe
        //section_header.mNumberOfLinenumbers  = 0;  // maybe
        //section_header.mCharacteristics      = 0;  // NOPE
        
        // Set section headers
        fseek(fp, (long)offset, SEEK_SET);
        if ((fwrite(&section_header, sizeof(section_header), 1, fp)) != 1) {
            std::cerr << "Failed to write section header: '" << section_header.mName << "' of '" << filename << "'." << std::endl;
            exit(errno);
        }
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}

void pe32::ProcessPe64(char* filename) {

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
    //optional_header.mBaseOfData                = 0;  // Sometimes but no
    //optional_header.mImageBase                 = 0;  // FUCK NO
    //optional_header.mSectionAlignment          = 0;  // NOPE
    //optional_header.mFileAlignment             = 0;  // NOOOOOOPE
    optional_header.mMajorOperatingSystemVersion = 0;  // OK
    optional_header.mMinorOperatingSystemVersion = 0;  // OK
    optional_header.mMajorImageVersion           = 0;  // OK
    optional_header.mMinorImageVersion           = 0;  // OK
    //optional_header.mMajorSubsystemVersion     = 0;  // needs specific value
    optional_header.mMinorSubsystemVersion       = 0;  // OK
    //optional_header.mWin32VersionValue         = 0;  // OK but probably not
    //optional_header.mSizeOfImage               = 0;  // NOPE
    //optional_header.mSizeOfHeaders             = 0;  // NOPE
    optional_header.mCheckSum                    = 0;  // OK probably not good
    //optional_header.mSubsystem                 = 0;  // nah
    //optional_header.mDllCharacteristics        = 0;  // hmmmm... maybe but probably not
    optional_header.mSizeOfStackReserve          = 0;  // OK
    optional_header.mSizeOfStackCommit           = 0;  // OK
    optional_header.mSizeOfHeapReserve           = 0;  // OK
    optional_header.mSizeOfHeapCommit            = 0;  // OK
    optional_header.mLoaderFlags                 = 0;  // OK but probably not
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

    // Zero out each section header
    for (unsigned i = 0; i < header.mNumberOfSections; i++) {
        Pe32SectionHeader section_header;
        long offset = sizeof(MsDosStub) + sizeof(Pe32Header) +
            header.mSizeOfOptionalHeader + i * sizeof(Pe32SectionHeader);

        // Get section header
        fseek(fp, offset, SEEK_SET);
        if ((fread(&section_header, sizeof(Pe32SectionHeader), 1, fp)) != 1) {
            std::cerr << "Failed to read section header of '" << filename << "'." << std::endl;
            exit(errno);
        }

        // Clear entries of section header
        memset(section_header.mName, 0, 8);          // yes....?
        //section_header.mVirtualSize          = 0;  // NOPE
        //section_header.mVirtualAddress       = 0;  // NOPE
        //section_header.mSizeOfRawData        = 0;  // NOPE
        //section_header.mPointerToRawData     = 0;  // NOPE
        //section_header.mPointerToRelocations = 0;  // maybe
        //section_header.mPointerToLinenumbers = 0;  // maybe
        //section_header.mNumberOfRelocations  = 0;  // maybe
        //section_header.mNumberOfLinenumbers  = 0;  // maybe
        //section_header.mCharacteristics      = 0;  // NOPE
        
        // Set section headers
        fseek(fp, (long)offset, SEEK_SET);
        if ((fwrite(&section_header, sizeof(section_header), 1, fp)) != 1) {
            std::cerr << "Failed to write section header: '" << section_header.mName << "' of '" << filename << "'." << std::endl;
            exit(errno);
        }
    }

    std::cout << filename << " successfully processed." << std::endl;

    fclose(fp);
    return;
}
