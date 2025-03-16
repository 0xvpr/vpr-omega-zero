#include "pe32.h"

#include "filetypes.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef union {
    Pe32OptionalHeader header32;
    Pe32PlusOptionalHeader header64;
} pe32_union_t;

bool process_pe32( const char* restrict  filename,
                   const flags_ptr_t     flags,
                   enum filetype_t       arch )
{
    assert((arch == pe_x86) || (arch == pe_x86_64));

    if ( !( flags->zero_all             ||
            flags->zero_headers         ||
            flags->zero_section_headers ||
            flags->zero_optional_headers ) )
    {
        fprintf(stderr, "No processing for '%s' to be completed.\n", filename);
        return 0;
    }

    Pe32Header   header = { 0 };
    pe32_union_t optional_header_u;
    size_t       optional_header_size =
        ((arch == pe_x86)*sizeof(Pe32OptionalHeader)) +       // 32 bit
        ((arch == pe_x86_64)*sizeof(Pe32PlusOptionalHeader)); // 64 bit

    FILE* fp = 0;
    if ( !(fp = fopen(filename, "rb+")) )
    {
        fprintf(stderr, "Failed to open '%s' for reading.\n", filename);
        return false;
    }

    bool zero_headers = flags->zero_all || flags->zero_headers;
    if (zero_headers)
    {
        // Get PE32 header
        fseek(fp, sizeof(MsDosStub), SEEK_SET);
        if ( ( fread((char *)&header, sizeof(header), 1, fp)) != 1)
        {
            fprintf(stderr, "Failed to read header of '%s'.\n", filename);
            fclose(fp);
            return false;
        }

        //
        // Clear header
        //

        //header.mMagic                = 0;  // NOPE
        //header.mMachine              = 0;  // NOPE
        header.mTimeDateStamp          = 0;  // OK
        //header.mNumberOfSymbols      = 0;  // NOPE
        //header.mCharacteristics      = 0;  // NOPE
        //header.mNumberOfSections     = 0;  // MAYBE - if mNumberOfSections is saved before clearing
        //header.mSizeOfOptionalHeader = 0;  // NOPE
        header.mPointerToSymbolTable   = 0;  // OK

        // Set PE32 header
        fseek(fp, sizeof(MsDosStub), SEEK_SET);
        if ( fwrite((char *)&header, sizeof(header), 1, fp) != 1 )
        {
            fprintf(stderr, "Failed to write header of '%s'.\n", filename);
            fclose(fp);
            return false;
        }
    }

    bool zero_optional_headers = flags->zero_all || flags->zero_optional_headers;
    if (zero_optional_headers)
    {
        // Get optional header
        fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
        if ( fread((char *)&optional_header_u, optional_header_size, 1, fp) != 1)
        {
            fprintf(stderr, "Failed to read optional header of '%s'.\n", filename);
            fclose(fp);
            return false;
        }

        // Clear Optional Header
        if (arch == pe_x86) // 32 bit
        {
            //optional_header_u.header32.mMagic                     = 0;  // NOPE
            optional_header_u.header32.mMajorLinkerVersion          = 0;  // OK
            optional_header_u.header32.mMinorLinkerVersion          = 0;  // OK
            optional_header_u.header32.mSizeOfCode                  = 0;  // OK
            optional_header_u.header32.mSizeOfInitializedData       = 0;  // OK
            optional_header_u.header32.mSizeOfUninitializedData     = 0;  // OK
            //optional_header_u.header32.mAddressOfEntryPoint       = 0;  // NOPE
            optional_header_u.header32.mBaseOfCode                  = 0;  // OK
            optional_header_u.header32.mBaseOfData                  = 0;  // OK
            //optional_header_u.header32.mImageBase                 = 0;  // FUCK NO
            //optional_header_u.header32.mSectionAlignment          = 0;  // NOPE
            //optional_header_u.header32.mFileAlignment             = 0;  // NO
            optional_header_u.header32.mMajorOperatingSystemVersion = 0;  // OK
            optional_header_u.header32.mMinorOperatingSystemVersion = 0;  // OK
            optional_header_u.header32.mMajorImageVersion           = 0;  // OK
            optional_header_u.header32.mMinorImageVersion           = 0;  // OK
            //optional_header_u.header32.mMajorSubsystemVersion     = 0;  // needs specific value
            optional_header_u.header32.mMinorSubsystemVersion       = 0;  // OK
            //optional_header_u.header32.mWin32VersionValue         = 0;  // OK but probably not
            //optional_header_u.header32.mSizeOfImage               = 0;  // NOPE
            //optional_header_u.header32.mSizeOfHeaders             = 0;  // NOPE
            optional_header_u.header32.mCheckSum                    = 0;  // OK
            //optional_header_u.header32.mSubsystem                 = 0;  // nah
            //optional_header_u.header32.mDllCharacteristics        = 0;  // hmmmm... maybe but probably not
            optional_header_u.header32.mSizeOfStackReserve          = 0;  // OK
            optional_header_u.header32.mSizeOfStackCommit           = 0;  // OK
            optional_header_u.header32.mSizeOfHeapReserve           = 0;  // OK
            optional_header_u.header32.mSizeOfHeapCommit            = 0;  // OK
            optional_header_u.header32.mLoaderFlags                 = 0;  // OK but probably not
            //optional_header_u.header32.mNumberOfRvaAndSizes       = 0;  // Absolutely the fuck not
        }
        else // 64 bit
        {
            //optional_header_u.header32.mMagic                     = 0;  // NOPE
            optional_header_u.header64.mMajorLinkerVersion          = 0;  // OK
            optional_header_u.header64.mMinorLinkerVersion          = 0;  // OK
            optional_header_u.header64.mSizeOfCode                  = 0;  // OK
            optional_header_u.header64.mSizeOfInitializedData       = 0;  // OK
            optional_header_u.header64.mSizeOfUninitializedData     = 0;  // OK
            //optional_header_u.header64.mAddressOfEntryPoint       = 0;  // NOPE
            optional_header_u.header64.mBaseOfCode                  = 0;  // OK
            //optional_header_u.header64.mImageBase                 = 0;  // FUCK NO
            //optional_header_u.header64.mSectionAlignment          = 0;  // NOPE
            //optional_header_u.header64.mFileAlignment             = 0;  // NO
            optional_header_u.header64.mMajorOperatingSystemVersion = 0;  // OK
            optional_header_u.header64.mMinorOperatingSystemVersion = 0;  // OK
            optional_header_u.header64.mMajorImageVersion           = 0;  // OK
            optional_header_u.header64.mMinorImageVersion           = 0;  // OK
            //optional_header_u.header64.mMajorSubsystemVersion     = 0;  // needs specific value
            optional_header_u.header64.mMinorSubsystemVersion       = 0;  // OK
            //optional_header_u.header64.mWin32VersionValue         = 0;  // OK but probably not
            //optional_header_u.header64.mSizeOfImage               = 0;  // NOPE
            //optional_header_u.header64.mSizeOfHeaders             = 0;  // NOPE
            optional_header_u.header64.mCheckSum                    = 0;  // OK
            //optional_header_u.header64.mSubsystem                 = 0;  // nah
            //optional_header_u.header64.mDllCharacteristics        = 0;  // hmmmm... maybe but probably not
            optional_header_u.header64.mSizeOfStackReserve          = 0;  // OK
            optional_header_u.header64.mSizeOfStackCommit           = 0;  // OK
            optional_header_u.header64.mSizeOfHeapReserve           = 0;  // OK
            optional_header_u.header64.mSizeOfHeapCommit            = 0;  // OK
            optional_header_u.header64.mLoaderFlags                 = 0;  // OK but probably not
            //optional_header_u.header32.mNumberOfRvaAndSizes       = 0;  // Absolutely the fuck not
        }

        // Set optional header
        fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
        if ( fwrite((char *)&optional_header_u, optional_header_size, 1, fp) != 1 )
        {
            fprintf(stderr, "Failed to write header of '%s'.\n", filename);
            fclose(fp);
            return false;
        }
    }
    
    //
    // Zero out each section header
    //
    
    bool zero_section_headers = flags->zero_all || flags->zero_section_headers;
    if (zero_section_headers)
    {
        for (unsigned i = 0; i < header.mNumberOfSections; i++) {
            Pe32SectionHeader section_header = { 0 };
            // Get section header
            long offset = (long)(sizeof(MsDosStub) + sizeof(Pe32Header) +
                header.mSizeOfOptionalHeader + i * sizeof(Pe32SectionHeader));
            fseek(fp, offset, SEEK_SET);
            if ( fread((char *)&section_header, sizeof(section_header), 1, fp) != 1 )
            {
                fprintf(stderr, "Failed to read section header of '%s'.\n", filename);
                fclose(fp);
                return false;
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
            
            // Set section header
            fseek(fp, offset, SEEK_SET);
            if ( fwrite((char *)&section_header, sizeof(section_header), 1, fp) != 1)
            {
                fprintf(stderr, "Failed to write section header: '%s' of '%s'.\n", section_header.mName, filename);
                fclose(fp);
                return false;
            }
        }
    }

    fclose(fp);
    return true;
}
