cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Common)

set(PUBLIC_HEADERS
    Integers.h
    Memory.h
    NumericCast.hpp
    OverloadMultiplexor.h
    Stl/Array.h
    Stl/HashMap.h
    Stl/Optional.h
    Stl/Queue.h
    String.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    Integers.cpp
    Memory.cpp
    NumericCast.cpp
    OverloadMultiplexor.cpp
    Stl/HashMap.cpp
    Stl/Array.cpp
    Stl/Optional.cpp
    Stl/Queue.cpp
    String.cpp
)
list(TRANSFORM SOURCES PREPEND "src/")

add_library(${TARGET_NAME} STATIC)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_sources(${TARGET_NAME} 
    PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    ${PUBLIC_HEADERS})
