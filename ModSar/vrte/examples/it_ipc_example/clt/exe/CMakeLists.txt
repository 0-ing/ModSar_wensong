# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_S") 
set(TARGET_NAME "ipc_example_clt")

find_package(GTest 1.8 REQUIRED CONFIG)
if(GTest_FOUND)
    message(STATUS "GTEST was found")
else()
    message(FATAL_ERROR, "GTEST was not found!")
endif()

add_executable(${TARGET_NAME}
    src/clt.cpp)

target_link_libraries(${TARGET_NAME}
    GTest::gtest_main
    GTest::gmock_main
    ${TARGET_NAME}_comapi
    it::utils)

vrteb_strip_debug(TARGET_NAME ${TARGET_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_SECONDARY_PATH}/opt/app PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
endif()
