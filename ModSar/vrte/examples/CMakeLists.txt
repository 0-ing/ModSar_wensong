# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
include(cmake/Helpers.cmake)

set(ARA_HEADER "ar_21_11")

set(MACHINE_DEFINITION_FS1_ARXML "${CMAKE_CURRENT_LIST_DIR}/cfg/${ARA_HEADER}/Machine_IT_UsrDoc_FS1.arxml")
set(MACHINE_DEFINITION_FS2_ARXML "${CMAKE_CURRENT_LIST_DIR}/cfg/${ARA_HEADER}/Machine_IT_UsrDoc_FS2.arxml")

set(SW_CLUSTER_DUMMY_ARXML ${CMAKE_CURRENT_LIST_DIR}/cfg/${ARA_HEADER}/AP_SWCL.arxml)

set(ECUCFG_FILES
    "COM_nodeData.ecucfg"
    )

add_subdirectory(sample_app)
add_subdirectory(IT_UsrDocMethod)
#add_subdirectory(it_ipc_example)
add_subdirectory(lcm_app_client)
#add_subdirectory(app_DemoServer)
#add_subdirectory(it_ipc_method)
#add_subdirectory(it_ipc_event)

