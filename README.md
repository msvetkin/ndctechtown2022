# Test project for NDCTechTown 2022

## vcpkg

Clone vcpkg repository:

```bash
git clone git@github.com:microsoft/vcpkg.git
```

Invoke bootstrap script on Unix:

```bash
./vcpkg/bootstrap-vcpkg.sh
```

Invoke bootstrap script on Windows:

```bash
./vcpkg/bootstrap-vcpkg.bat
```

Build with simple manifest:

```bash
cmake -B build/vcpkg/simple -S . \
      -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
      -DVCPKG_MANIFEST_DIR=./package-managers/vcpkg/simple

cmake --build build/vcpkg/simple
```

Build with extend manifest:
```bash
cmake -B build/vcpkg/extended -S . \
      -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
      -DVCPKG_MANIFEST_DIR=./package-managers/vcpkg/extended

cmake --build build/vcpkg/extended
```

Build with cmake presets:

```

cmake --preset vcpkg-simple
cmake --build --preset vcpkg-simple

cmake --preset vcpkg-extended
cmake --build --preset vcpkg-extended

```

## conan

Install and setup

```bash
pip install conan
conan profile update settings.compiler.libcxx=libstdc++11 default
```

Build with conanfile.txt

```bash
mkdir -p build/conan/txt && cd build/conan/txt
conan install ../../../package-managers/conan/txt
cmake ../../../ \
    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Build with conanfile.py

```bash
conan install -if build/conan/py -of build/conan/py package-managers/conan/py/
conan build -if build/conan/py -bf build/conan/py -sf .  package-managers/conan/py
```
