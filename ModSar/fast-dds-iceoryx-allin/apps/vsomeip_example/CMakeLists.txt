# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8.7)
project (vSomeIPHelloWorld)

find_package(Threads REQUIRED)
set(VSOMEIP_NAME vsomeip3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (${CMAKE_SYSTEM_NAME} MATCHES "QNX")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "QNX")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3.linux)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3.linux/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3.linux/lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


find_package(${VSOMEIP_NAME})
if (NOT ${VSOMEIP_NAME}_FOUND)
    message("${VSOMEIP_NAME} was not found. Please specify vsomeip_DIR")
endif()

add_library(vsomeip_hello_world_service INTERFACE)
target_sources(vsomeip_hello_world_service INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/hello_world_service.hpp"
)
target_include_directories(vsomeip_hello_world_service INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(vsomeip_hello_world_client INTERFACE)
target_sources(vsomeip_hello_world_client INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/hello_world_client.hpp"
)
target_include_directories(vsomeip_hello_world_client INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )
# This will get us acces to
#   VSOMEIP_INCLUDE_DIRS - include directories for vSomeIP
#   VSOMEIP_LIBRARIES    - libraries to link against
message("${VSOMEIP_INCLUDE_DIRS} ${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ")

add_executable (hello_world_service hello_world_service_main.cpp)
target_link_libraries(hello_world_service vsomeip_hello_world_service -l${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable (hello_world_client hello_world_client_main.cpp)
target_link_libraries(hello_world_client vsomeip_hello_world_client -l${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
