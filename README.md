<h1 align="center">vpr-omega-zero</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Windows-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Mac-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Linux-supported-44CC11"/>
  <a href="https://mit-license.org/"/>
    <img src="https://img.shields.io/badge/License-MIT-44CC11"/>
  </a>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/vpr-omega-zero/build.yml?label=Build"/>
</p>
<h3 align="center">Inspired by yellobytes's <a href="https://github.com/yellowbyte/reverse-engineering-playground/tree/master/file_format_hacks">zeroSection2.py</a></h3>
<br>

This project aims to provide a tool for the stripping of the  
section-header information of 32/64 bit ELF and PE32 executables.

## Building with Docker (recommended)
```
# Download repo
git clone https://github.com/0xvpr/vpr-omega-zero
cd vpr-omega-zero

# Create docker image and build with cmake
chmod +x docker-build.sh && ./docker-build.sh
```

## Build instructions (local)
Windows/Linux/WSL/MSYS/macOS
```bash
git clone https://github.com/0xvpr/vpr-omega-zero vpr-omega-zero
cd vpr-omega-zero
cmake -B build
cmake --build build
```

## Example Usage
```bash
Usage:
  vpr-omega-zero.exe [<optional_arguments>] <path/to/executable-1> <path/to/executable-2>

Optional arguments:
  -a,                Enable all flags. (default option)
  --all
  -o,                Zero all optional headers.
  --optional-headers
  -s,                Zero all section headers.
  --section-headers
  -H                 Zero all headers.
  -headers
  -h,                Display help.
  --help

Examples:
  vpr-omega-zero.exe path/to/executable
  vpr-omega-zero.exe -sH path/to/executable

Version:
  1.1.0

Author:
  VPR
```

#### Testing
[ TODO ]
