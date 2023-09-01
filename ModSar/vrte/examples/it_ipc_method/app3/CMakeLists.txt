# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

set(TARGET_NAME "IT_Methods_app3")

add_executable(${TARGET_NAME}
    src/app3.cpp)

target_link_libraries(${TARGET_NAME}
    ${TARGET_NAME}_comapi
    it::utils)

#add_dependencies(${THIS_TEST_NAME}
#    ${TARGET_NAME})

#install(
#    TARGETS ${TARGET_NAME}
#    DESTINATION ${INSTALL_FOLDER}/hk/opt/app
#    COMPONENT ${THIS_TEST_NAME}
#    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
vrteb_strip_debug(TARGET_NAME ${TARGET_NAME} INSTALL_STRIPPED_DIR /hk/opt/app PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
