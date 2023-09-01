# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2020. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

set(CURRENT_TEST_NAME "it_method")
set(TARGET_NAME "${CURRENT_TEST_NAME}_publisher")

#################################################   FINDING NEEDED PACKAGES BELOW  ##############################################################################################
### ARA::COM
find_package(com-communication-manager CONFIG REQUIRED)

### ARA::LOG
find_package(log-framework-if CONFIG REQUIRED)

### ARA::EXEC
find_package(exm-executionclient-lib CONFIG REQUIRED)
add_executable(${TARGET_NAME}
    publisher.cpp)

   file(GLOB_RECURSE ARXML_FILES "${PROJ_ROOT}/../com/interfaces/Method.arxml" 
	   "${PROJ_ROOT}/ecu_cfg/w3.3_m_machine/executable/IT_UsrDocMethod/Apps_IT_UsrDocMethod.arxml"
	   "${PROJ_ROOT}/../com/deployments/w3.3_m_instances/IT_Method_ServiceInstanceManifest.arxml")

   add_vrte_comapi_library(${CURRENT_TEST_NAME}_comapi 
        PROXIES  "com/bosch/vrte/method/method"                              
        SKELETONS  "com/bosch/vrte/method/method"                                  
	ARXMLS  ${ARXML_FILES}                        
        GEN_SRC "${CMAKE_CURRENT_BINARY_DIR}/_gen"                       
    )

target_link_libraries(${TARGET_NAME}
    ${CURRENT_TEST_NAME}_comapi
    ${LOG_FRAMEWORK_IF_LIBRARIES})

#add_dependencies(${TARGET_NAME}
#    ${CURRENT_TEST_NAME}_ecucfg
#    ${CURRENT_TEST_NAME}_dsomeip)

#install(
#    TARGETS ${TARGET_NAME} 
#    DESTINATION ${INSTALL_FOLDER}/bin/FS1
#    COMPONENT ${CURRENT_TEST_NAME}
#    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)

#install the binary
if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P")
vrteb_strip_debug(TARGET_NAME ${TARGET_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_PRIMARY_PATH}/opt/app/example/bin)
endif()

