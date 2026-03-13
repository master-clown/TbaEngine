#!/bin/bash

if [ $# -eq 1 ]; then
    targetDir=$1
else
    targetDir="."
fi

function generateProfile() {
    buildType="$1"

cat << EOF > ${targetDir}/tba_engine_${buildType,,}
[settings]
arch=x86_64
build_type=${buildType}
compiler=clang
compiler.cppstd=26
compiler.libcxx=libstdc++11
compiler.version=20
os=Linux

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:exelinkflags=["-fuse-ld=lld", "-Wl,--undefined-version"]
tools.build:sharedlinkflags=["-fuse-ld=lld", "-Wl,--undefined-version"]
tools.build:compiler_executables={"cpp": "clang++", "c": "clang"}
tools.cmake.cmaketoolchain:extra_variables={"CMAKE_CXX_COMPILER_LAUNCHER": "/usr/bin/ccache", "CMAKE_C_COMPILER_LAUNCHER": "/usr/bin/ccache"}
EOF
}

generateProfile Debug
generateProfile RelWithDebInfo
generateProfile Release
