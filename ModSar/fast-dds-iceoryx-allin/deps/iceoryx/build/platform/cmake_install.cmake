# Install script for directory: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_platform

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/iceoryx_platform" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_platform/LICENSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xbinx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/libiceoryx_platform.a")
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
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/include/iceoryx/v" TYPE DIRECTORY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_platform/linux/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformConfigVersion.cmake;/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform" TYPE FILE FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/iceoryx_platformConfigVersion.cmake"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/iceoryx_platformConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake"
         "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform" TYPE FILE FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/CMakeFiles/Export/_home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/iceoryx_platformTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/IceoryxPackageHelper.cmake;/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform/IceoryxPlatformSettings.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/cmake/iceoryx_platform" TYPE FILE FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_platform/cmake/IceoryxPackageHelper.cmake"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_platform/linux/IceoryxPlatformSettings.cmake"
    )
endif()

