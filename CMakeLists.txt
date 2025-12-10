cmake_minimum_required(VERSION 3.10)

project(GuiTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(src)
