# *************************************************************************
# *                                                                       *
# *                      ROBERT BOSCH GMBH                                *
# *                          STUTTGART                                    *
# *                                                                       *
# *          Alle Rechte vorbehalten - All rights reserved                *
# *                                                                       *
# *************************************************************************

cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(ARA_VERSION ar-21-11)
project(Lcm_Demo_Client-project LANGUAGES CXX)

if(DEFINED PINTEAM_LINUX)
    list(APPEND CMAKE_MODULE_PATH "$ENV{SDK_PATH}/opt/vrte/lib/cmake/vrteb_fs")
    list(APPEND CMAKE_MODULE_PATH "$ENV{SDK_PATH}/opt/vrte/lib/cmake")
endif()

if(DEFINED PINTEAM_LINUX)
    # the MISC_ROOT_DIR has to point to a different locaction
    set(MISC_ROOT_DIR $ENV{SDK_PATH}/usr/bin)
endif()

# Do not allow in-source builds.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

#project(lcm-demo-client-project
#    VERSION 22.8.0
#    DESCRIPTION "VRTE STM Project")

option(CPPCHECK               "Run cppcheck for static code analysis."              OFF)
option(CPPLINT                "Run cpplint for static code analysis."               OFF)
option(CLANG_TIDY             "Run clang-tidy for static code analysis."            OFF)
option(LCOV_COVERAGE          "Enable lcov code coverage analysis in unit tests."   OFF)
option(CTC_COVERAGE           "Enable ctc code coverage analysis in unit tests."    OFF)
option(SKIP_GEN               "Skip code generation."                               OFF)
option(MAPFILE                "Enable map file generation"                           ON)
option(UNIT_TEST              "Build unit tess"                                     OFF)
option(COMPONENT_TEST         "Build component tests"                               OFF)
option(BUILD_STATIC_LIBS      "Build plugins as static libs"                        OFF)
option(CREATE_IF_PACKAGE_ONLY "Only create the ARXML IF package."                   OFF)

message(STATUS "ENV{QNX_HOST} = $ENV{QNX_HOST}")
message(STATUS "ENV{QNX_TARGET} = $ENV{QNX_TARGET}")

# We need to have a toolchain file with QCC set and environment variables QNX_TARGET and QNX_HOST set.
# This is due to the fact that aracom does only allow a small set of compilers.
# Also the qcc compiler requires the two environment variables to be set.
if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "{PROJECT_NAME} cannot be built without a toolchain file and some env variables."
                        "Example:\n"
                        "\texport RB_VRTE_dependencies=\"../_dep_QNX_x86_64\"\n"
                        "\texport QNX_TARGET=\"/home/$USER/qnx700_7.0-platform-20201123/host/linux/x86_64\"\n"
                        "\texport QNX_TARGET=\"/home/$USER/qnx700_7.0-platform-20201123/target/qnx7\"\n"
                        "\tcmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/defaultToolchain.cmake")
endif()

# Enable static analysis tools.
if(CPPCHECK OR CPPLINT OR CLANG_TIDY)
    include(staticAnalysis)
endif()

if( DEFINED PINTEAM_LINUX )
    ## add -O3 in order to handle undefined references when static variables are declared and defined in hpp files.
    add_definitions(-DPINTEAM_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(STM_LINK_DIAG_LIBS 0) # do not link diag libs
else()
    set(STM_LINK_DIAG_LIBS 1)
endif()


if("${ARA_VERSION}" STREQUAL "ar-20-11")
    add_definitions(-DARA_VERSION_20_11)
endif()

message(STATUS "VRTE State Manager Project")
message(STATUS ">>>> -----------------------------------------")
message(STATUS ">>>> PROJECT: ${PROJECT_NAME}")
message(STATUS ">>>> VERSION: ${PROJECT_VERSION}")
message(STATUS ">>>> -----")
message(STATUS ">>>> ARA_VERSION:        ${ARA_VERSION}")
message(STATUS ">>>> CMAKE_C_COMPILER:   ${CMAKE_C_COMPILER}")
message(STATUS ">>>> CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS ">>>> CMAKE_AR:           ${CMAKE_AR}")
message(STATUS ">>>> CMAKE_RANLIB:       ${CMAKE_RANLIB}")
message(STATUS ">>>> CMAKE_LINKER:       ${CMAKE_LINKER}")
message(STATUS ">>>> CMAKE_CXX_FLAGS     ${CMAKE_CXX_FLAGS}")


if(NOT CREATE_IF_PACKAGE_ONLY)
    # generate the phm headers from the arxml file which defines a supervised entry
    include(vrteb_fs_cli)

    #set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${STM_GENERIC_CMAKE_DIR}")
			
	# Provide the software components as a static library. These also build the proxy skeletons.
    add_subdirectory(Components/Cmp_DemoClient)

    # create an executable which uses the generated static libraries above.
    add_subdirectory(Executables)

endif(NOT CREATE_IF_PACKAGE_ONLY)