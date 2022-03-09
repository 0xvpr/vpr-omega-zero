# vpr-zero-sections
Inspired by yellobytes's <a href="https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks">zeroSection2.py</a>  

This project aim's to provide a tool for the stripping of the  
section-header information of ELF and PE32 executables.

## Build instructions
```bash
git clone https://github.com/0xvpr/vpr-zero-sections
cd vpr-zero-sections
make
sudo make install # if you want it available globally
```

## Example Usage
```bash
vpr-zero-sections path/to/executable
```
