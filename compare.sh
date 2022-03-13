#!/bin/bash

# Creator:    VPR
# Created:    March 9th, 2022
# Creator:    March 10th, 2022

declare -a objects=("Tests/PE/pe_x86.exe"
                    "Tests/PE/pe_x86_64.exe"
                    "Tests/ELF/elf_x86.exe"
                    "Tests/ELF/elf_x86_64.exe")

oz="omega-zero.txt"
original="original.txt"
results="results.txt"

if ! [ -f ./Bin/vpr-omega-zero ];
then
    make release
fi

make tests
for i in "${objects[@]}"
do
    ./Bin/vpr-omega-zero "${i}"
    objdump -fs --section-headers "${i}" >> "${oz}"
done

make tests
for i in "${objects[@]}"
do
    objdump -fs --section-headers "${i}" >> "${original}"
done

diff ${oz} ${original} > ${results}
diff ${oz} ${original} | wc

rm ${oz} ${original}
#rm ${results}
