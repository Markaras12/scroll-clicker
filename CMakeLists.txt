cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

# ── Geode SDK ────────────────────────────────────────────
# Point GEODE_SDK to your local Geode SDK clone, e.g.:
#   cmake -DGEODE_SDK=/path/to/geode ..
# or set the environment variable GEODE_SDK before running cmake.

if (NOT DEFINED ENV{GEODE_SDK})
    if (NOT DEFINED GEODE_SDK)
        message(FATAL_ERROR
            "GEODE_SDK is not defined.\n"
            "Set it via -DGEODE_SDK=<path> or the GEODE_SDK environment variable."
        )
    endif()
else()
    set(GEODE_SDK $ENV{GEODE_SDK})
endif()

set(CMAKE_MODULE_PATH "${GEODE_SDK}/cmake;${CMAKE_MODULE_PATH}")

# ── Project ───────────────────────────────────────────────
project(scroll-clicker VERSION 1.0.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Required Geode boilerplate
setup_geode_mod(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
