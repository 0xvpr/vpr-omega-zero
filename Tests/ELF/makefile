all: x86 x86_64

x86: 
	g++ -m32 -g elf.cpp -o elf_x86.exe

x86_64:
	g++ -m64 -g elf.cpp -o elf_x86_64.exe

clean:
	rm -fr *.exe
