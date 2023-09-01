include_directories(
    ${PROJECT_SOURCE_DIR}/deps/boost_1_55_tiny/include
)

set(LIB_SRCS
src/codecvt_error_category.cpp
src/operations.cpp
src/path.cpp
src/path_traits.cpp
src/portability.cpp
src/unique_path.cpp
src/utf8_codecvt_facet.cpp
src/windows_file_codecvt.cpp
)


add_library(boost_filesystem ${LIB_SRCS})
target_link_libraries(boost_filesystem)
