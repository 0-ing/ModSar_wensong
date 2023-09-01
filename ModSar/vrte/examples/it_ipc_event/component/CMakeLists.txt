# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2019. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
 
### ARA::COM
find_package(com-communication-manager CONFIG REQUIRED)

set(SOFTWARE_COMPONENT_NAME "IT_Event_app1")
#################################################   FINDING NEEDED PACKAGES ABOVE  ##############################################################################################

### generate C++ src files from ARXML files
set(ARXML_FILES 
    # Interfaces:
    ${PROJ_ROOT}/com/interfaces/IT_Event_ServiceManifest.arxml
    ${CMAKE_CURRENT_LIST_DIR}/arxml/IT_IPC_Event_App1_Component.arxml
)

set(PROXIES
    "com/bosch/vrte/com/it/ipc/iapp1notification"
    "com/bosch/vrte/com/it/ipc/iapp2notification"
    "com/bosch/vrte/com/it/ipc/servicecontroller")

set(SKELETONS
    "com/bosch/vrte/com/it/ipc/iapp1notification"
    "com/bosch/vrte/com/it/ipc/iapp2notification"
    "com/bosch/vrte/com/it/ipc/servicecontroller")

add_vrte_comapi_library (${SOFTWARE_COMPONENT_NAME}_comapi VERBOSE
       PROXIES
           ${PROXIES}
       SKELETONS
           ${SKELETONS}
       ARXMLS
           ${ARXML_FILES}
       GEN_SRC
           ${CMAKE_BINARY_DIR}/gen/${SOFTWARE_COMPONENT_NAME}
)


set(SOFTWARE_COMPONENT_NAME "IT_Event_app2")
#################################################   FINDING NEEDED PACKAGES ABOVE  ##############################################################################################

### generate C++ src files from ARXML files
set(ARXML_FILES 
    # Interfaces:
    ${PROJ_ROOT}/com/interfaces/IT_Event_ServiceManifest.arxml
    ${CMAKE_CURRENT_LIST_DIR}/arxml/IT_IPC_Event_App2_Component.arxml
)

set(PROXIES
    "com/bosch/vrte/com/it/ipc/iapp1notification"
    "com/bosch/vrte/com/it/ipc/iapp2notification"
    "com/bosch/vrte/com/it/ipc/servicecontroller")

set(SKELETONS
    "com/bosch/vrte/com/it/ipc/iapp1notification"
    "com/bosch/vrte/com/it/ipc/iapp2notification"
    "com/bosch/vrte/com/it/ipc/servicecontroller")

add_vrte_comapi_library (${SOFTWARE_COMPONENT_NAME}_comapi VERBOSE
       PROXIES
           ${PROXIES}
       SKELETONS
           ${SKELETONS}
       ARXMLS
           ${ARXML_FILES}
       GEN_SRC
           ${CMAKE_BINARY_DIR}/gen/${SOFTWARE_COMPONENT_NAME}
)


