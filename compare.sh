#!/bin/bash

# Creator:    VPR
# Created:    March 9th, 2022
# Creator:    March 10th, 2022

declare -a objects=("Tests/ELF/elf_x86.exe" "Tests/ELF/elf_x86_64.exe")
vpr="vpr.txt"
yellowbyte="yellowbyte.txt"

if ! [ -f ./Bin/vpr-zero-sections ];
then
    make release
fi

make tests
for i in "${objects[@]}"
do
    ./Bin/vpr-zero-sections "${i}"
    objdump -fs "${i}"   >> "${vpr}"
    readelf -lh "${i}"   >> "${vpr}"
done

if ! [ -f ./zeroSection2.py ];
then
    wget https://raw.githubusercontent.com/yellowbyte/reverse-engineering-playground/master/file_format_hacks/zeroSection2.py
fi

make tests
for i in "${objects[@]}"
do
    python2 ./zeroSection2.py "${i}"
    objdump -fs "${i}"     >> "${yellowbyte}"
    readelf -lh "${i}"     >> "${yellowbyte}"
done

diff ${vpr} ${yellowbyte} -q
diff ${vpr} ${yellowbyte} | wc

rm zeroSection2.py
rm ${vpr} ${yellowbyte}
