# Install script for directory: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_binding_c

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/iceoryx_binding_c" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_binding_c/LICENSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xbinx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/libiceoryx_binding_c.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v" TYPE DIRECTORY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_binding_c/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cConfigVersion.cmake;/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c" TYPE FILE FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/iceoryx_binding_cConfigVersion.cmake"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/iceoryx_binding_cConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake"
         "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_binding_c/iceoryx_binding_cTargets-release.cmake")
  endif()
endif()

