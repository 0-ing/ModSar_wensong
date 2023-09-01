
#################################################################################
#                  common parts for all cmake scripts                           #
#            just copy as the beginning of root CMakeLists.txt                  #
#################################################################################

cmake_minimum_required(VERSION 3.1.3)
project(helloworld C CXX)

if (DEFINED RULE_DIR)
    include(${RULE_DIR}/rule_base.cmake)
else()
    set(RULE_DIR ${CMAKE_SOURCE_DIR})
    include(rule_base.cmake)
endif()

set(PACKAGE_SOURCE_ROOT ${CMAKE_SOURCE_DIR})


print_variable(PACKAGE_SOURCE_ROOT)
print_variable(BUILD_OUT)

#################################################################################
#                cmake script for project-specific package                      #
#################################################################################

file(GLOB HELLOWORLD_SRC "${PACKAGE_SOURCE_ROOT}/src/*.cpp")

add_executable(helloworld ${HELLOWORLD_SRC})

install(TARGETS helloworld DESTINATION ${BUILD_OUT})
