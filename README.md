<h1 align="center">vpr-omega-zero</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Windows-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Mac-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Linux-supported-44CC11"/>
  <a href="https://mit-license.org/"/>
    <img src="https://img.shields.io/badge/License-MIT-44CC11"/>
  </a>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/vpr-omega-zero/docker_build.yml?label=Build"/>
</p>
<h3 align="center">Inspired by yellobytes's <a href="https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks">zeroSection2.py</a></h3>
<br>

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
