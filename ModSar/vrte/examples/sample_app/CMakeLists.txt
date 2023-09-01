# *************************************************************************
# *                                                                       *
# *                      ROBERT BOSCH GMBH                                *
# *                          STUTTGART                                    *
# *                                                                       *
# *          Alle Rechte vorbehalten - All rights reserved                *
# *                                                                       *
# *************************************************************************
 
cmake_minimum_required(VERSION 3.12)

# Set the EXE_APP_NAME
set(EXE_APP_NAME "Exe_Sample_App")
set(PROJECT_NAME ${EXE_APP_NAME})

#needed to navigate more easily from software component cmake file to needed arxml files
set(EXECUTABLE_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Change the name of the project and the executable name (project name = executable name)
project(${PROJECT_NAME} LANGUAGES CXX)

# Provide the software components as a static library. These also build the proxy skeletons.

# create an executable which uses the generated static libraries above.
add_subdirectory(exe)

# install the target
#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /hk/opt/app PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)

#Workaround for 21-08, fix logging warning ringbuffer overflow
#Install ara-log library with increased ringbuffer size
#In 22-01 the ringbuffer size will be configurable
