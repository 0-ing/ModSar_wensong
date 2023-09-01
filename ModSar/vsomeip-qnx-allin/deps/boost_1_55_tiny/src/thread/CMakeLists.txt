include_directories(
    ${PROJECT_SOURCE_DIR}/deps/boost_1_55_tiny/include
)

set(LIB_SRCS
src/pthread/thread.cpp
src/pthread/once.cpp
src/future.cpp
)


add_library(boost_thread ${LIB_SRCS})
target_link_libraries(boost_thread)
