cmake_minimum_required(VERSION 3.24)

project(TbaEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(AVAILABLE_COMPILE_OPTIONS
    ENABLE_LOG
    OPENGL_USE_BINDLESS_TEXTURES
)
foreach(option IN LISTS AVAILABLE_COMPILE_OPTIONS)
    if(${${option}})
        message(STATUS "Adding option ${option}")
        add_compile_definitions(${option})
    endif()
endforeach()

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(src)
add_subdirectory(test)
