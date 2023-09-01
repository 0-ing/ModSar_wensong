# Install script for directory: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_dust

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xbinx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/libiceoryx_dust.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v/;/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v" TYPE DIRECTORY FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_dust/include/"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_dust/vocabulary/include/"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustConfigVersion.cmake;/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust" TYPE FILE FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/iceoryx_dustConfigVersion.cmake"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/iceoryx_dustConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake"
         "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_dust/iceoryx_dustTargets-release.cmake")
  endif()
endif()

