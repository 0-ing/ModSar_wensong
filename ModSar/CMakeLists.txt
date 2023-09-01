
cmake_minimum_required(VERSION 3.1.3)
project(ModSAR C CXX)

set( CMAKE_VERBOSE_MAKEFILE on )
include(CMakePrintHelpers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

cmake_print_variables(PROJECT_SOURCE_DIR)

message(STATUS "build type:")
message(STATUS "CXX_FLAGS = ${CMAKE_CXX_FLAGS} ")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/inc
    )

