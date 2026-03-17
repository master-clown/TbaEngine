import sys

from pathlib import Path

def printToFile(fileName, text):
    with open(fileName, "w") as file:
        file.write(text)

def makeProfileFilePath(targetDir, buildType: str):
    return Path(targetDir) / f"tba_engine_{buildType.lower()}"

def generateProfileForLinux(targetDir, buildType):
    text = f"""
[settings]
os=Linux
arch=x86_64
build_type={buildType}
compiler=clang
compiler.version=20
compiler.cppstd=23
compiler.libcxx=libstdc++11

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.build:exelinkflags=["-fuse-ld=lld", "-Wl,--undefined-version"]
tools.build:sharedlinkflags=["-fuse-ld=lld", "-Wl,--undefined-version"]
tools.build:compiler_executables={{"cpp": "clang++", "c": "clang"}}
tools.cmake.cmaketoolchain:extra_variables={{"CMAKE_CXX_COMPILER_LAUNCHER": "/usr/bin/ccache", "CMAKE_C_COMPILER_LAUNCHER": "/usr/bin/ccache"}}
"""

    printToFile(makeProfileFilePath(targetDir, buildType), text)

def generateProfileForWindows(targetDir, buildType):
    text = f"""
[settings]
os=Windows
arch=x86_64
build_type={buildType}
compiler=msvc
compiler.version=195
compiler.cppstd=23
compiler.runtime=dynamic

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
tools.cmake.cmaketoolchain:extra_variables={{"CMAKE_CXX_COMPILER_LAUNCHER": "ccache", "CMAKE_C_COMPILER_LAUNCHER": "ccache"}}
tools.build:cxxflags=["/Zc:preprocessor"]
"""

    printToFile(makeProfileFilePath(targetDir, buildType), text)


def main():
    targetDir = "." if len(sys.argv) < 2 else sys.argv[1]

    generateProfile = \
            (lambda a1, a2: generateProfileForWindows(a1, a2)) \
            if sys.platform == "win32" \
            else (lambda a1, a2: generateProfileForLinux(a1, a2))
        
    generateProfile(targetDir, "Debug")
    generateProfile(targetDir, "RelWithDebInfo")
    generateProfile(targetDir, "Release")


if __name__ == "__main__":
    main()  
