include_directories(
    ${PROJECT_SOURCE_DIR}/deps/boost_1_55_tiny/include
)

set(LIB_SRCS
src/error_code.cpp
)


add_library(boost_system ${LIB_SRCS})
target_link_libraries(boost_system)
