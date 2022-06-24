# tiny video player

This project is a prototype of a simple video player based on FFmpeg libraries (for video decoding) and on Dear ImGui (for UI).

---

## Prerequisites
- CMake
- Python3
- Ninja
- MSVC (on Windows), GCC or Clang (on Linux/Mac)

## Setup Conan
```bash
pip install conan
```

## Configure Dependencies
```bash
./conan/run_conan.sh <Debug|Release> # Linux/Mac
conan\run_conan.bat <Debug|Release> # Windows
```

## Configure Project
```bash
cmake -G Ninja -D CMAKE_BUILD_TYPE=<Debug|Release> -B ./build/<Debug|Release> -S .
```

## Build Project
```bash
cmake --build ./build/<Debug|Release> --config <Debug|Release>
```