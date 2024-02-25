cmake_minimum_required(VERSION 3.5)

project(reedsolomon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
add_definitions(-D__GFPoly_=285)

set(HEADERS_SOLOMONLIB
        include/ghalua_byte.hpp
        include/ghalua_poly.hpp
    )

set(SOURCE_SOLOMONLIB
        src/ghalua_byte.cpp
        src/ghalua_poly.cpp
    )

add_library(reedsolomonlib STATIC ${HEADERS_SOLOMONLIB} ${SOURCE_SOLOMONLIB})

set(HEADERS_MATHLIB
        include/ghalua_math.hpp
    )
set(SOURCES_MATHLIB
        src/ghalua_math.cpp
    )

add_library(ghaluamathlib STATIC ${HEADERS_MATHLIB} ${SOURCES_MATHLIB})

add_executable(reedsolomon_test src/test.cpp)
target_link_libraries(reedsolomon_test reedsolomonlib ghaluamathlib)
