if (${CMAKE_SYSTEM_NAME} MATCHES "QNX")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "QNX")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux)
set(VSOMEIP_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux/include)
set(VSOMEIP_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux/lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


message("${VSOMEIP_INCLUDE} xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")

set(LIB_SRCS
    sugar/com/any.cpp
    sugar/com/common.cpp
    sugar/com/event.cpp
    sugar/com/field.cpp
    sugar/com/method.cpp
    sugar/com/sync.cpp
    sugar/proxy/runtime.cpp
    sugar/skeleton/runtime.cpp
    sugar/skeleton.cpp
    sugar/proxy.cpp
    sugar/instance_identifier.cpp
    vsomeip-wrapper/sugar/SugarVSomeipProxy.cpp
    vsomeip-wrapper/sugar/SugarVSomeipSkeleton.cpp
    mts/MTSLogic.cpp
)

set(fastcdr_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/Fast-DDS/install/lib/cmake/fastcdr)
set(fastrtps_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/Fast-DDS/install/share/fastrtps/cmake)
set(foonathan_memory_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/Fast-DDS/install/lib/foonathan_memory/cmake)

set(iceoryx_platform_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/lib/cmake/iceoryx_platform)
set(iceoryx_posh_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/lib/cmake/iceoryx_posh)
set(iceoryx_hoofs_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/lib/cmake/iceoryx_hoofs)
set(iceoryx_dust_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/lib/cmake/iceoryx_dust)
include(GNUInstallDirs)
find_package(iceoryx_platform REQUIRED)
find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_hoofs CONFIG REQUIRED)
find_package(iceoryx_dust CONFIG REQUIRED)
include(IceoryxPackageHelper)
include(IceoryxPlatform)
include(IceoryxPlatformSettings)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

message(${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/include/iceoryx/v)
set(XXX ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/iceoryx/install/include/iceoryx/v)




include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/src
    ${VSOMEIP_INCLUDE}
    ${fastcdr_INCLUDE_DIR}
    ${XXX}

)
set(IOX_VERSION_STRING "2.90.0")
set(PREFIX iceoryx/v${CMAKE_PROJECT_VERSION})
LINK_DIRECTORIES(
    ${PROJECT_BINARY_DIR}/lib
    ${VSOMEIP_LIB}
    ${fastcdr_LIB_DIR}
    ${ICEORYX_SRCS}
)

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++14 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++14)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++14")
    endif()
endif()


set(DDS_SRCS
    sugar/com/dds_event.cpp
    fastdds-wrapper/SugarFastDDSPublisher.cpp
    fastdds-wrapper/SugarFastDDSSubscriber.cpp
    fastdds-wrapper/protocol/HelloWorld.cxx
    fastdds-wrapper/protocol/HelloWorldPubSubTypes.cxx
)
set(ICEORYX_SRCS
    iceoryx-wrapper/SharedObjectPublisher.cpp
    iceoryx-wrapper/SharedObjectSubscribler.cpp
)

#iox_add_library(
#    NO_EXPORT
#    NO_PACKAGE_SETUP
#    NO_FIND_PACKAGE_SUPPORT
#    TARGET              iceory_wrapper
#    NAMESPACE           sugar
#    PROJECT_PREFIX      ${PREFIX}
##    #BUILD_INTERFACE     ${XXX}
#    INSTALL_INTERFACE   include/${PREFIX}
#    PUBLIC_INCLUDES     ${XXX}
#    PUBLIC_LIBS         iceoryx_hoofs::iceoryx_hoofs
#                        iceoryx_posh::iceoryx_posh
#    FILES  ${ICEORYX_SRCS}
#)

add_library(sugar ${LIB_SRCS} ${DDS_SRCS} ${ICEORYX_SRCS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set_target_properties(sugar PROPERTIES OUTPUT_NAME "sugar")


