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
CMAKE_SOURCE_DIR = /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux

# Include any dependencies generated for this target.
include examples/CMakeFiles/subscribe-sample.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/subscribe-sample.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/subscribe-sample.dir/flags.make

examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o: examples/CMakeFiles/subscribe-sample.dir/flags.make
examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o: ../examples/subscribe-sample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o -c /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/examples/subscribe-sample.cpp

examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.i"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/examples/subscribe-sample.cpp > CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.i

examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.s"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/examples/subscribe-sample.cpp -o CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.s

# Object files for target subscribe-sample
subscribe__sample_OBJECTS = \
"CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o"

# External object files for target subscribe-sample
subscribe__sample_EXTERNAL_OBJECTS =

examples/subscribe-sample: examples/CMakeFiles/subscribe-sample.dir/subscribe-sample.cpp.o
examples/subscribe-sample: examples/CMakeFiles/subscribe-sample.dir/build.make
examples/subscribe-sample: libvsomeip3.so.3.1.20
examples/subscribe-sample: examples/CMakeFiles/subscribe-sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable subscribe-sample"
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/subscribe-sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/subscribe-sample.dir/build: examples/subscribe-sample

.PHONY : examples/CMakeFiles/subscribe-sample.dir/build

examples/CMakeFiles/subscribe-sample.dir/clean:
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples && $(CMAKE_COMMAND) -P CMakeFiles/subscribe-sample.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/subscribe-sample.dir/clean

examples/CMakeFiles/subscribe-sample.dir/depend:
	cd /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/examples /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples /home/iwl1wx/bosch/ModSar/fast-dds-iceoryx-allin/deps/vsomeip-qnx/build_linux/examples/CMakeFiles/subscribe-sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/subscribe-sample.dir/depend

