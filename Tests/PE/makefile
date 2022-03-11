all: x86 x86_64

x86:
	i686-w64-mingw32-g++-posix -g pe.cpp -o pe_x86.exe -lmsvcrt -lkernel32 -lpthread -static -s

x86_64:
	x86_64-w64-mingw32-g++-posix -g pe.cpp -o pe_x86_64.exe -lmsvcrt -lkernel32 -lpthread -static -s

clean:
	rm -fr *.exe
