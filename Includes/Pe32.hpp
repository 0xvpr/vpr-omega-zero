#ifndef PE_32_HEADER
#define PE_32_HEADER

#include <cstdint>

// Structs
namespace pe32 {

    typedef struct _MsDosStub {
        uint16_t mMagic;
        unsigned char bits[126];
    } MsDosStub;

    typedef struct _Pe32Header {
        uint32_t mMagic; // PE\0\0 or 0x00004550
        uint16_t mMachine;
        uint16_t mNumberOfSections;
        uint32_t mTimeDateStamp;
        uint32_t mPointerToSymbolTable;
        uint32_t mNumberOfSymbols;
        uint16_t mSizeOfOptionalHeader;
        uint16_t mCharacteristics;
    } Pe32Header;

    typedef struct _Pe32OptionalHeader {
        uint16_t mMagic; // 0x010b - PE32, 0x020b - PE32+ (64 bit)
        uint8_t  mMajorLinkerVersion;
        uint8_t  mMinorLinkerVersion;
        uint32_t mSizeOfCode;
        uint32_t mSizeOfInitializedData;
        uint32_t mSizeOfUninitializedData;
        uint32_t mAddressOfEntryPoint;
        uint32_t mBaseOfCode;
        uint32_t mBaseOfData;
        uint32_t mImageBase;
        uint32_t mSectionAlignment;
        uint32_t mFileAlignment;
        uint16_t mMajorOperatingSystemVersion;
        uint16_t mMinorOperatingSystemVersion;
        uint16_t mMajorImageVersion;
        uint16_t mMinorImageVersion;
        uint16_t mMajorSubsystemVersion;
        uint16_t mMinorSubsystemVersion;
        uint32_t mWin32VersionValue;
        uint32_t mSizeOfImage;
        uint32_t mSizeOfHeaders;
        uint32_t mCheckSum;
        uint16_t mSubsystem;
        uint16_t mDllCharacteristics;
        uint32_t mSizeOfStackReserve;
        uint32_t mSizeOfStackCommit;
        uint32_t mSizeOfHeapReserve;
        uint32_t mSizeOfHeapCommit;
        uint32_t mLoaderFlags;
        uint32_t mNumberOfRvaAndSizes;
    } Pe32OptionalHeader;

    typedef struct _Pe32SectionHeader {
        char     mName[8];
        uint32_t mVirtualSize;
        uint32_t mVirtualAddress;
        uint32_t mSizeOfRawData;
        uint32_t mPointerToRawData;
        uint32_t mPointerToRelocations;
        uint32_t mPointerToLinenumbers;
        uint16_t mNumberOfRelocations;
        uint16_t mNumberOfLinenumbers;
        uint32_t mCharacteristics;
    } Pe32SectionHeader;

} // namespace pe32

// Functions
namespace pe32 {

    /**
     * Perform scraping of 32 bit PE32 binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessPe32(char*);

    /**
     * Perform scraping of 64 bit PE32+ binary.
     *
     * @param    filename
     * @return   void
    **/
    void ProcessPe64(char*);

} // namespace pe32

#endif // PE_32_HEADER
