# Install script for directory: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/iceoryx" TYPE FILE FILES
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../doc/website/FAQ.md"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../doc/website/getting-started/overview.md"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../doc/website/advanced/installation-guide-for-contributors.md"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../LICENSE"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../NOTICE.md"
    "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../README.md"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/iceoryx" TYPE DIRECTORY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../doc/3rd_party_licenses")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/iceoryx" TYPE DIRECTORY FILES "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/iceoryx_meta/../doc/website/release-notes")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/platform/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/hoofs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/dust/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/posh/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/iceoryx_binding_c/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
