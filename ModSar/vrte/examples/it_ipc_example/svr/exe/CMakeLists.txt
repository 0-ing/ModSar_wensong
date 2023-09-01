# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P") 
set(TARGET_NAME "ipc_example_svr")

add_executable(${TARGET_NAME}
    src/svr.cpp)

target_link_libraries(${TARGET_NAME}
    ${TARGET_NAME}_comapi
    it::utils)

vrteb_strip_debug(TARGET_NAME ${TARGET_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_PRIMARY_PATH}/opt/app PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
endif()
