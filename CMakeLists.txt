cmake_minimum_required(VERSION 3.5)

project(reedsolomon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_definitions(-D__GFPoly_=285)
add_definitions(-D__ENABLE_TESTS_)

set(HEADERS_SOLOMONLIB
        include/reedsolomon/ghalua_math.hpp
        include/reedsolomon/ghalua_byte.hpp
        include/reedsolomon/ghalua_poly.hpp
    )

set(SOURCE_SOLOMONLIB
        src/ghalua_byte.cpp
        src/ghalua_poly.cpp
    )

add_library(reedsolomon STATIC ${HEADERS_SOLOMONLIB} ${SOURCE_SOLOMONLIB})


add_executable(reedsolomon_devtest src/devtest.cpp)
target_link_libraries(reedsolomon_devtest reedsolomon)
