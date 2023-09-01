# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2019. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
 
#include(/home/lol3sgh/opt/VRTE/R22-04/6i/SDKs/qnx_x86_64/fs1/target/opt/vrte/lib/cmake/com-communication-manager/VrteComApi.cmake)
### ARA::COM
#find_package(com-communication-manager CONFIG REQUIRED)
#add_library(${SOFTWARE_COMPONENT_NAME} STATIC)

#target_sources(${SOFTWARE_COMPONENT_NAME}
#    PRIVATE
#        ${PROJ_ROOT}/app_CPTestClient/Interface/CPTestClient/src/CPTestClient.cpp
#)
#################################################   FINDING NEEDED PACKAGES ABOVE  ##############################################################################################

### generate C++ src files from ARXML files
include(vrteb_fs_cli)

find_package(com-communication-manager CONFIG REQUIRED)
set(ARXML_FILES 
    # Interfaces:
    ${PROJ_ROOT}/com/interfaces/ipc_example_ServiceManifest.arxml
    ${CMAKE_CURRENT_LIST_DIR}/arxml/ipc_example_svrComponent.arxml
    ${CMAKE_CURRENT_LIST_DIR}/../exe/arxml/Exe_ipc_example_svr_ExecutionManifest.arxml
    #${CMAKE_CURRENT_LIST_DIR}/../exe/arxml/ipc_example_svr_ServiceInstanceManifest.arxml
)

# trigger generation of skeletons via vrteb module

set(PROXIES
    "com/bosch/vrte/com/example/iseed"
    "com/bosch/vrte/com/example/isum")

set(SKELETONS
    "com/bosch/vrte/com/example/iseed"
    "com/bosch/vrte/com/example/isum")

set(SOFTWARE_COMPONENT_NAME "ipc_example_svr")
add_vrte_comapi_library(${SOFTWARE_COMPONENT_NAME}_comapi VERBOSE
       PROXIES
           ${PROXIES} 
       SKELETONS
           ${SKELETONS}
       ARXMLS
           ${ARXML_FILES}
       GEN_SRC
       ${CMAKE_BINARY_DIR}/gen/${SOFTWARE_COMPONENT_NAME}
)

