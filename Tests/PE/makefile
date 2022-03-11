all: x86 x86_64

x86:
	i686-w64-mingw32-g++-posix -g pe.cpp -o pe_x86.exe

x86_64:
	x86_64-w64-mingw32-g++-posix -g pe.cpp -o pe_x86_64.exe

clean:
	rm -fr *.exe
