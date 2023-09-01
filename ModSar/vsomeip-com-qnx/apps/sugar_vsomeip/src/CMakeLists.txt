if (${CMAKE_SYSTEM_NAME} MATCHES "QNX")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../deps/vsomeip3.3/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "QNX")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux)
set(VSOMEIP_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux/include)
set(VSOMEIP_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux/lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/src
    ${VSOMEIP_INCLUDE}
)
LINK_DIRECTORIES(
    ${PROJECT_BINARY_DIR}/lib
    ${VSOMEIP_LIB}
)

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

add_library(sugar ${LIB_SRCS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set_target_properties(sugar PROPERTIES OUTPUT_NAME "sugar")


