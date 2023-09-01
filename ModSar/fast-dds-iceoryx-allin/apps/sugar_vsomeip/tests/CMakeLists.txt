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


add_executable (test_cs_server cs_server.cpp)
target_link_libraries(test_cs_server -l${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} sugar)

add_executable (test_cs_client cs_client.cpp)
target_link_libraries(test_cs_client -l${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} sugar)