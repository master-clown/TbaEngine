cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Framework)

set(PUBLIC_HEADERS
    Framework.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/Framework/")

set(SOURCES
    ${PUBLIC_HEADERS}
    src/Framework.cpp
)

find_package(SDL3 REQUIRED)

add_library(${TARGET_NAME} STATIC)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE SDL3::SDL3)
