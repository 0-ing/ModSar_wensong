# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

set(TARGET_NAME "IT_Event_app1")

get_filename_component(GTEST_PATH "${PROJ_ROOT}/prebuild/qnx_${ARCHITECTURE}/lib/cmake/GTest" ABSOLUTE) # get absoulte gtestpath

#include GTest from QNX SDK
list(APPEND CMAKE_MODULE_PATH ${GTEST_PATH}) # including gtest module path to cmake include module path
list(APPEND CMAKE_FIND_ROOT_PATH ${GTEST_PATH}) # including gtest module path to cmakefind module path
message(${CMAKE_MODULE_PATH})
enable_testing()

find_package(GTest 1.8 REQUIRED CONFIG)
if(GTest_FOUND)
    message(STATUS "GTEST was found")
else()
    message(FATAL_ERROR, "GTEST was not found!")
endif()

add_executable(${TARGET_NAME}
    app1.cpp)

target_link_libraries(${TARGET_NAME}
    GTest::gtest_main
    GTest::gmock_main
    ${TARGET_NAME}_comapi
    it::utils)

install(
    TARGETS ${TARGET_NAME}
    DESTINATION ${INSTALL_FOLDER}/hk/opt/app
    COMPONENT ${THIS_TEST_NAME}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
