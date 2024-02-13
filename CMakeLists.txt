cmake_minimum_required(VERSION 3.5)

project(reedsolomon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_LIB
        src/ghalua_byte.cpp
        src/ghalua_poly.cpp
    )

set(HEADERS_LIB
        include/ghalua_byte.hpp
        include/ghalua_poly.hpp
    )

include_directories(include)

add_library(reedsolomon STATIC ${HEADERS_LIB} ${SOURCE_LIB})

add_executable(reedsolomon_test src/main.cpp)
target_link_libraries(reedsolomon_test reedsolomon)
