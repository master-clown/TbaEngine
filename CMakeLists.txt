cmake_minimum_required(VERSION 3.24)

project(TbaEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if(ENABLE_LOG)
    add_compile_definitions(ENABLE_LOG)
endif()

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(src)
add_subdirectory(test)
