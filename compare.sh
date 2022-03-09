#!/bin/bash

# Creator:    VPR
# Created:    March 9th, 2022
# Creator:    March 9th, 2022

object=Tests/ELF/elf.exe
vpr="vpr.txt"
yellow="yellowbyte.txt"

if ! [ -f ./Bin/vpr-zero-sections ];
then
    make
fi

( cd Tests/ELF && make )
./Bin/vpr-zero-sections "${object}"
objdump -fs "${object}"  > "${vpr}"
readelf -h "${object}"  >> "${vpr}"
readelf -l "${object}"  >> "${vpr}"

if ! [ -f ./zeroSection2.py ];
then
    wget https://raw.githubusercontent.com/yellowbyte/reverse-engineering-playground/master/file_format_hacks/zeroSection2.py
fi

( cd Tests/ELF && make )
python2 ./zeroSection2.py "${object}"
objdump -fs "${object}"  > "${yellow}"
readelf -h "${object}"  >> "${yellow}"
readelf -l "${object}"  >> "${yellow}"

diff ${vpr} ${yellow}

rm zeroSection2.py
rm ${vpr} ${yellow}
