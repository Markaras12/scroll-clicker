cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    if (NOT DEFINED GEODE_SDK)
        message(FATAL_ERROR "GEODE_SDK is not defined.")
    endif()
else()
    set(GEODE_SDK $ENV{GEODE_SDK})
endif()

file(TO_CMAKE_PATH "${GEODE_SDK}" GEODE_SDK)

list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK}/cmake")

include("${GEODE_SDK}/cmake/GeodeFile.cmake")

project(scroll-clicker VERSION 1.0.0)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

setup_geode_mod(${PROJECT_NAME})
