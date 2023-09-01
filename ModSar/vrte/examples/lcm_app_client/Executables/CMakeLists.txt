# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2019. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
 

# Set the EXE_APP_NAME.
set(EXE_APP_NAME "DemoClient")
set(PROJECT_NAME "Exe_${EXE_APP_NAME}")

set(STM_PROJECT_FILE_PATH ${ROOT_DIR}/../../../lcm/)
set(VRTE_COMMON_FILE_PATH ${ROOT_DIR}/../../../com/)

# Change the name of the project and the executable name (project name = executable name).
project(${PROJECT_NAME} LANGUAGES CXX)

# Define the "executable-part" of the application (everything that is in the Executables folder).
add_executable(${PROJECT_NAME} _src/Exe_DemoClient.cpp)
#################################################   FINDING NEEDED PACKAGES BELOW  ##############################################################################################

### ARA::COM
find_package(com-communication-manager CONFIG REQUIRED)

### ARA::LOG
find_package(log-framework-if CONFIG REQUIRED)

### ARA::EXEC
find_package(exm-executionclient-lib CONFIG REQUIRED)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${com-communication-manager_LIBRARIES}
        ${EXM_EXECUTIONCLIENT_LIB_LIBRARIES}
        ${log-framework-if_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    	${com-communication-manager_INCLUDE_DIRS}
    	${log-framework-if_INCLUDE_DIRS}
)
#################################################   FINDING NEEDED PACKAGES ABOVE  #############################################################################################################
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Cmp_DemoClient
)

# Include the proxy-skeleton directory which has been generated in the SWC-Cmake-List. They are needed
# for the included files in the src-file
message(STATUS ">>>> Cmp_DemoClient.hpp -> ${VRTE_COMMON_FILE_PATH}")
target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_BINARY_DIR}/gen/Cmp_DemoClient
        ${CMAKE_CURRENT_LIST_DIR}/../Components/Cmp_DemoClient/_inc
        ${VRTE_COMMON_FILE_PATH}/CEL/Component/_inc
        ${Boost_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME}  ARCHIVE DESTINATION ${INSTALL_PATH_LIB})

#vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /fs1/opt/app)
#install the binary
if(DEFINED WAVE3_VARIANT)
    if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P") 
        vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_PRIMARY_PATH}/opt/app)
    elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.3_S") 
        vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_SECONDARY_PATH}/opt/app)
    elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.2") 
        vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.2_PATH}/opt/app)
    endif()
endif()
