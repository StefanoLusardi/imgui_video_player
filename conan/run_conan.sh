BUILD_TYPE=$1
echo BUILD_TYPE: $BUILD_TYPE

export CC=gcc-10
export CXX=g++-10
export CONAN_SYSREQUIRES_SUDO=1
export CONAN_SYSREQUIRES_MODE=enabled
export DEBIAN_FRONTEND=noninteractive

conan install . \
    --settings build_type=$BUILD_TYPE \
    --install-folder build/$BUILD_TYPE/modules \
    --build missing