# vpr-omega-zero
Inspired by yellobytes's <a href="https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks">zeroSection2.py</a>  

This project aims to provide a tool for the stripping of the  
section-header information of 32/64 bit ELF and PE32 executables.

## Docker Environment
```
# Download repo
git clone https://github.com/0xvpr/vpr-omega-zero
cd vpr-omega-zero

# Create docker image
chmod +x docker-build.sh && ./docker-build.sh
chmod +x docker-start.sh && ./docker-start.sh
```

## Build instructions
```bash
git clone https://github.com/0xvpr/vpr-omega-zero
cd vpr-omega-zero
make
sudo make install # if you want it available globally
```

## Example Usage
```bash
vpr-omega-zero path/to/executable [ path/to/other/executable ]
```

## Testing (Needs improvement)
```bash
chmod +x compare.sh && ./compare.sh
```
