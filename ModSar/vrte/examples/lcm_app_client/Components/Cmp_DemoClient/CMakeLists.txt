# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2019. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
 

set(SOFTWARE_COMPONENT_NAME Cmp_DemoClient)

set(STM_PROJECT_FILE_PATH ${ROOT_DIR}/../../../lcm)
set(VRTE_COMMON_FILE_PATH ${ROOT_DIR}/../../../com)

add_library(${SOFTWARE_COMPONENT_NAME} STATIC)

target_sources(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/_src/${SOFTWARE_COMPONENT_NAME}.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientAppAraCompStateRequestProxy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientAppAraCompStateStatusService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientAppCompStateRequestProxy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientAppCompStateStatusService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientComponentClientImpl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/_src/Cmp_DemoClientLogger.cpp
)

#################################################   FINDING NEEDED PACKAGES BELOW  ##############################################################################################

### ARA::LOG
find_package(log-framework-if)

### ARA::EXEC
find_package(exm-executionclient-lib)

### ARA::COM
find_package(com-communication-manager)


target_link_libraries(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${com-communication-manager_LIBRARIES}
        ${log-framework-if_LIBRARIES}
)


target_include_directories(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${com-communication-manager_INCLUDE_DIRS}
        ${log-framework-if_INCLUDE_DIRS}
)

#################################################   FINDING NEEDED PACKAGES ABOVE  ##############################################################################################
target_include_directories(${SOFTWARE_COMPONENT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/_inc
        ${CMAKE_CURRENT_LIST_DIR}/_inc/interface/
    PRIVATE
        ${CMAKE_BINARY_DIR}/gen/${SOFTWARE_COMPONENT_NAME}
        ${VRTE_COMMON_FILE_PATH}/CEL/Component/_inc
)

### generate C++ src files from ARXML files
include(vrteb_fs_cli)

set(ARXML_FILES 
    # ###################### #
    # Executable Specific    #
    # ###################### #
    ${ROOT_DIR}/Executables/arxml/Exe_DemoClient_Instances.arxml
    ${ROOT_DIR}/Executables/arxml/Exe_DemoClient_Executable.arxml
    # ###################### #
    # Component Specific     #
    # ###################### #
    ${ROOT_DIR}/Components/Cmp_DemoClient/arxml/Cmp_DemoClient.arxml
    # Deployments:
    #${PROJ_ROOT}/Common/Platform/PA3/Deployments/arxml/Svi_Demo_deployment.arxml
    # Interfaces:
    #${ROOT_DIR}/Interfaces/Svi_Demo.arxml

    # DefaultFG and SysModeFG
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerinout-statedefaultfg.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerinout-statesysmodefg.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-datatypes.arxml
    # Generic Trigger in
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerin_generic.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-triggerin_generic.arxml

    # OSM State
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerout_osmstate.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-triggerout_osmstate.arxml

    # CMP State
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-componentstaterequest.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerout_componentstaterequest.arxml
    # sysmoderequestStatus
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerout_componentstatestatus.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-required-port-componentstatestatus.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-datatypes.arxml
    # SysModeRequest
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-triggerinout_sysmoderequest.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerinout_sysmoderequest.arxml
    # TestClientRequest
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-triggerinout_testclientrequest.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerinout_testclientrequest.arxml
    # TestModeRequest
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-provided-port-triggerinout_testmoderequest.arxml
    ${STM_PROJECT_FILE_PATH}/arxml/stm-aap-state-manager-triggerinout_testmoderequest.arxml
    # ###################### #
    # AUTOSAR  Platformtypes #
    # ###################### #
    ${VRTE_COMMON_FILE_PATH}/CEL/AUTOSAR_Platform/_arxml/Adaptive_PlatformTypes.arxml
    ${VRTE_COMMON_FILE_PATH}/CEL/AUTOSAR_Platform/_arxml/Platform_Types_AdaptiveExtension.arxml   
)

# trigger generation of skeletons via vrteb module
set(skeleton_lib_name_${SOFTWARE_COMPONENT_NAME} svi_${SOFTWARE_COMPONENT_NAME}_skeleton_lib)
set(proxy_lib_name_${SOFTWARE_COMPONENT_NAME} svi_${SOFTWARE_COMPONENT_NAME}_proxy_lib)
vrteb_generate_comapi(
    SERVICE 
        #rb.pt.vehfct.drvdemdet.detnpedl.svi_demo
        ara.sm.default_fg.triggerinout_statedefaultfg
        ara.sm.sysmode_fg.triggerinout_statesysmodefg
        ara.sm.triggerout_osmstate
        ara.sm.triggerout_componentstaterequest
        ara.sm.triggerout_componentstatestatus
        bosch.vrte.sm.triggerin_generic
        ara.sm.sysmode_request.triggerinout_sysmoderequest
        ara.sm.testclient_request.triggerinout_testclientrequest
        ara.sm.testmode_request.triggerinout_testmoderequest
    OUTDIR ${CMAKE_BINARY_DIR}/gen/${SOFTWARE_COMPONENT_NAME}
    PROXY_LIB ${proxy_lib_name_${SOFTWARE_COMPONENT_NAME}}
    SKELETON_LIB ${skeleton_lib_name_${SOFTWARE_COMPONENT_NAME}}
    ARXML ${ARXML_FILES}
)

target_link_libraries(${SOFTWARE_COMPONENT_NAME}
    PRIVATE
        ${skeleton_lib_name_${SOFTWARE_COMPONENT_NAME}}
        ${proxy_lib_name_${SOFTWARE_COMPONENT_NAME}}
)
