cmake_minimum_required(VERSION 3.5)

project(reedsolomon LANGUAGES CXX)

option(ENABLE_TESTS "" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_definitions(-D__GFPoly_=285)

set(HEADERS_SOLOMONLIB
        include/reedsolomon/ghalua_math.hpp
        include/reedsolomon/ghalua_byte.hpp
        include/reedsolomon/ghalua_poly.hpp
        include/reedsolomon/encoder.hpp
    )

set(SOURCE_SOLOMONLIB
        src/ghalua_byte.cpp
        src/ghalua_poly.cpp
        src/encoder.cpp
    )

add_library(reedsolomon STATIC ${HEADERS_SOLOMONLIB} ${SOURCE_SOLOMONLIB})

if(ENABLE_TESTS)
    Include(FetchContent)

    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    set(TESTS_SOURCES
            test/test_gfByte.cpp
            test/test_gfPoly.cpp
            test/test_encoder.cpp
        )
    add_executable(test ${TESTS_SOURCES})
    target_link_libraries(test PRIVATE
            Catch2::Catch2WithMain
            reedsolomon
        )
endif()
