# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1

# Include any dependencies generated for this target.
include sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/depend.make

# Include the progress variables for this target.
include sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/progress.make

# Include the compile flags for this target's objects.
include sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/flags.make

sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.o: sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/flags.make
sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.o: ../sugar_vsomeip/samples/zerocopy_helloworld/testServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.o"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testServer.dir/testServer.cpp.o -c /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/sugar_vsomeip/samples/zerocopy_helloworld/testServer.cpp

sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testServer.dir/testServer.cpp.i"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/sugar_vsomeip/samples/zerocopy_helloworld/testServer.cpp > CMakeFiles/testServer.dir/testServer.cpp.i

sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testServer.dir/testServer.cpp.s"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/sugar_vsomeip/samples/zerocopy_helloworld/testServer.cpp -o CMakeFiles/testServer.dir/testServer.cpp.s

# Object files for target testServer
testServer_OBJECTS = \
"CMakeFiles/testServer.dir/testServer.cpp.o"

# External object files for target testServer
testServer_EXTERNAL_OBJECTS =

../sugar_vsomeip/home/tests/testServer: sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/testServer.cpp.o
../sugar_vsomeip/home/tests/testServer: sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/build.make
../sugar_vsomeip/home/tests/testServer: sugar_vsomeip/lib/libsugar.a
../sugar_vsomeip/home/tests/testServer: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/libiceoryx_posh.a
../sugar_vsomeip/home/tests/testServer: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/libiceoryx_dust.a
../sugar_vsomeip/home/tests/testServer: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/libiceoryx_hoofs.a
../sugar_vsomeip/home/tests/testServer: /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/iceoryx/install/lib/libiceoryx_platform.a
../sugar_vsomeip/home/tests/testServer: sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../sugar_vsomeip/home/tests/testServer"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/build: ../sugar_vsomeip/home/tests/testServer

.PHONY : sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/build

sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/clean:
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld && $(CMAKE_COMMAND) -P CMakeFiles/testServer.dir/cmake_clean.cmake
.PHONY : sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/clean

sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/depend:
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/sugar_vsomeip/samples/zerocopy_helloworld /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1 /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/apps/build_linux_1/sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sugar_vsomeip/samples/zerocopy_helloworld/CMakeFiles/testServer.dir/depend

