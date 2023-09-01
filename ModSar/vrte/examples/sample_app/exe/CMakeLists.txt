# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2019. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------
 
# Set the EXE_APP_NAME.
set(EXE_APP_NAME "Exe_Sample_App")
set(PROJECT_NAME ${EXE_APP_NAME})

# Change the name of the project and the executable name (project name = executable name).
project(${PROJECT_NAME} LANGUAGES CXX)

# Define the "executable-part" of the application (everything that is in the Executables folder).
if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P") 
add_executable(${PROJECT_NAME} src/main.cpp)
elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.3_S") 
add_executable(${PROJECT_NAME} src/main2.cpp)
elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.2") 
add_executable(${PROJECT_NAME} src/main3.cpp)
endif()

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
        ${log-framework-if_LIBRARIES}
        ${exm-executionclient-lib_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    	${com-communication-manager_INCLUDE_DIRS}
    	${log-framework-if_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# Define the "executable-part" of the application (everything that is in the Executables folder).
if(${WAVE3_BUILD_TYPE} STREQUAL "debug") 
	message("Build debug version")
elseif(${WAVE3_BUILD_TYPE} STREQUAL "release") 
	message("Build release version")
endif()

#install the binary
if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P") 
vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_PRIMARY_PATH}/opt/app/example/bin)
elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.3_S") 
vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.3_SECONDARY_PATH}/opt/app/example/bin)
elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.2") 
vrteb_strip_debug(TARGET_NAME ${PROJECT_NAME} INSTALL_STRIPPED_DIR /${WAVE3.2_PATH}/opt/app)
endif()

