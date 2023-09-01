

if (${CMAKE_SYSTEM_NAME} MATCHES "QNX")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "QNX")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(vsomeip_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux)
set(vsomeip_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/vsomeip3.3.linux/include)
set(vsomeip_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../../deps/vsomeip3.3.linux/lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


find_package(${VSOMEIP_NAME})
if (NOT ${VSOMEIP_NAME}_FOUND)
    message("${VSOMEIP_NAME} was not found. Please specify vsomeip_DIR")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/inc
    ${vsomeip_INCLUDE}
)
LINK_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/lib
    ${vsomeip_LIB}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/home/tests)
add_executable(testproxy proxy.cpp )

target_link_libraries(testproxy sugar -l${VSOMEIP_LIBRARIES} pthread)


add_executable(testskeleton skeleton.cpp )

target_link_libraries(testskeleton sugar -l${VSOMEIP_LIBRARIES} pthread )

