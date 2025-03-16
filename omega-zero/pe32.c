#include "pe32.h"

#include "filetypes.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef union {
    Pe32OptionalHeader header32;
    Pe32PlusOptionalHeader header64;
} pe32_union_t;

bool process_pe32(const char* restrict filename, const flags_ptr_t flags, enum filetype_t arch)
{
    assert((arch == pe_x86) || (arch == pe_x86_64));

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

    // Get PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ( ( fread((char *)&header, sizeof(header), 1, fp)) != 1)
    {
        fprintf(stderr, "Failed to read header of '%s'.\n", filename);
        fclose(fp);
        return false;
    }

    // Get optional header
    fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
    if ( fread((char *)&optional_header_u, optional_header_size, 1, fp) != 1)
    {
        fprintf(stderr, "Failed to read optional header of '%s'.\n", filename);
        fclose(fp);
        return false;
    }

    //
    // Clear header
    //

    bool zero_headers =
        !(flags->zero_all || flags->zero_headers);
    //header.mMagic                *= zero_headers;  // NOPE
    //header.mMachine              *= zero_headers;  // NOPE
    header.mTimeDateStamp          *= zero_headers;  // OK
    //header.mNumberOfSymbols      *= zero_headers;  // NOPE
    //header.mCharacteristics      *= zero_headers;  // NOPE
    //header.mNumberOfSections     *= zero_headers;  // MAYBE - if mNumberOfSections is saved before clearing
    //header.mSizeOfOptionalHeader *= zero_headers;  // NOPE
    header.mPointerToSymbolTable   *= zero_headers;  // OK

    //
    // Clear Optional Header
    //

    bool zero_sections =
        !(flags->zero_all || flags->zero_sections);
    if (arch == pe_x86) // 32 bit
    {
        //optional_header_u.header32.mMagic                     *= zero_sections;  // NOPE
        optional_header_u.header32.mMajorLinkerVersion          *= zero_sections;  // OK
        optional_header_u.header32.mMinorLinkerVersion          *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfCode                  *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfInitializedData       *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfUninitializedData     *= zero_sections;  // OK
        //optional_header_u.header32.mAddressOfEntryPoint       *= zero_sections;  // NOPE
        optional_header_u.header32.mBaseOfCode                  *= zero_sections;  // OK
        optional_header_u.header32.mBaseOfData                  *= zero_sections;  // OK
        //optional_header_u.header32.mImageBase                 *= zero_sections;  // FUCK NO
        //optional_header_u.header32.mSectionAlignment          *= zero_sections;  // NOPE
        //optional_header_u.header32.mFileAlignment             *= zero_sections;  // NO
        optional_header_u.header32.mMajorOperatingSystemVersion *= zero_sections;  // OK
        optional_header_u.header32.mMinorOperatingSystemVersion *= zero_sections;  // OK
        optional_header_u.header32.mMajorImageVersion           *= zero_sections;  // OK
        optional_header_u.header32.mMinorImageVersion           *= zero_sections;  // OK
        //optional_header_u.header32.mMajorSubsystemVersion     *= zero_sections;  // needs specific value
        optional_header_u.header32.mMinorSubsystemVersion       *= zero_sections;  // OK
        //optional_header_u.header32.mWin32VersionValue         *= zero_sections;  // OK but probably not
        //optional_header_u.header32.mSizeOfImage               *= zero_sections;  // NOPE
        //optional_header_u.header32.mSizeOfHeaders             *= zero_sections;  // NOPE
        optional_header_u.header32.mCheckSum                    *= zero_sections;  // OK
        //optional_header_u.header32.mSubsystem                 *= zero_sections;  // nah
        //optional_header_u.header32.mDllCharacteristics        *= zero_sections;  // hmmmm... maybe but probably not
        optional_header_u.header32.mSizeOfStackReserve          *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfStackCommit           *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfHeapReserve           *= zero_sections;  // OK
        optional_header_u.header32.mSizeOfHeapCommit            *= zero_sections;  // OK
        optional_header_u.header32.mLoaderFlags                 *= zero_sections;  // OK but probably not
        //optional_header_u.header32.mNumberOfRvaAndSizes       *= zero_sections;  // Absolutely the fuck not
    }
    else // 64 bit
    {
        //optional_header_u.header32.mMagic                     *= zero_sections;  // NOPE
        optional_header_u.header64.mMajorLinkerVersion          *= zero_sections;  // OK
        optional_header_u.header64.mMinorLinkerVersion          *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfCode                  *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfInitializedData       *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfUninitializedData     *= zero_sections;  // OK
        //optional_header_u.header64.mAddressOfEntryPoint       *= zero_sections;  // NOPE
        optional_header_u.header64.mBaseOfCode                  *= zero_sections;  // OK
        //optional_header_u.header64.mImageBase                 *= zero_sections;  // FUCK NO
        //optional_header_u.header64.mSectionAlignment          *= zero_sections;  // NOPE
        //optional_header_u.header64.mFileAlignment             *= zero_sections;  // NO
        optional_header_u.header64.mMajorOperatingSystemVersion *= zero_sections;  // OK
        optional_header_u.header64.mMinorOperatingSystemVersion *= zero_sections;  // OK
        optional_header_u.header64.mMajorImageVersion           *= zero_sections;  // OK
        optional_header_u.header64.mMinorImageVersion           *= zero_sections;  // OK
        //optional_header_u.header64.mMajorSubsystemVersion     *= zero_sections;  // needs specific value
        optional_header_u.header64.mMinorSubsystemVersion       *= zero_sections;  // OK
        //optional_header_u.header64.mWin32VersionValue         *= zero_sections;  // OK but probably not
        //optional_header_u.header64.mSizeOfImage               *= zero_sections;  // NOPE
        //optional_header_u.header64.mSizeOfHeaders             *= zero_sections;  // NOPE
        optional_header_u.header64.mCheckSum                    *= zero_sections;  // OK
        //optional_header_u.header64.mSubsystem                 *= zero_sections;  // nah
        //optional_header_u.header64.mDllCharacteristics        *= zero_sections;  // hmmmm... maybe but probably not
        optional_header_u.header64.mSizeOfStackReserve          *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfStackCommit           *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfHeapReserve           *= zero_sections;  // OK
        optional_header_u.header64.mSizeOfHeapCommit            *= zero_sections;  // OK
        optional_header_u.header64.mLoaderFlags                 *= zero_sections;  // OK but probably not
        //optional_header_u.header32.mNumberOfRvaAndSizes       *= zero_sections;  // Absolutely the fuck not
    }

    // Set PE32 header
    fseek(fp, sizeof(MsDosStub), SEEK_SET);
    if ( fwrite((char *)&header, sizeof(header), 1, fp) != 1 )
    {
        fprintf(stderr, "Failed to write header of '%s'.\n", filename);
        fclose(fp);
        return false;
    }

    // Set optional header
    fseek(fp, sizeof(MsDosStub) + sizeof(Pe32Header), SEEK_SET);
    if ( fwrite((char *)&optional_header_u, optional_header_size, 1, fp) != 1 )
    {
        fprintf(stderr, "Failed to write header of '%s'.\n", filename);
        fclose(fp);
        return false;
    }
    
    //
    // Zero out each section header name
    //
    
    bool zero_names = !(flags->zero_all || flags->zero_names);
    if (!zero_names)
    {
        for (unsigned i = 0; i < header.mNumberOfSections; i++) {
            Pe32SectionHeader section_header;
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
            
            // Set section headers
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
