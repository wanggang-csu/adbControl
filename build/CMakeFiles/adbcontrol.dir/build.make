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
CMAKE_SOURCE_DIR = /home/wg/01_workspace/96tmpg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wg/01_workspace/96tmpg/build

# Include any dependencies generated for this target.
include CMakeFiles/adbcontrol.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/adbcontrol.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/adbcontrol.dir/flags.make

CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o: CMakeFiles/adbcontrol.dir/flags.make
CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o: ../src/adb/ADBControl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wg/01_workspace/96tmpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o -c /home/wg/01_workspace/96tmpg/src/adb/ADBControl.cpp

CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wg/01_workspace/96tmpg/src/adb/ADBControl.cpp > CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.i

CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wg/01_workspace/96tmpg/src/adb/ADBControl.cpp -o CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.s

# Object files for target adbcontrol
adbcontrol_OBJECTS = \
"CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o"

# External object files for target adbcontrol
adbcontrol_EXTERNAL_OBJECTS =

libadbcontrol.so: CMakeFiles/adbcontrol.dir/src/adb/ADBControl.cpp.o
libadbcontrol.so: CMakeFiles/adbcontrol.dir/build.make
libadbcontrol.so: CMakeFiles/adbcontrol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wg/01_workspace/96tmpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libadbcontrol.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/adbcontrol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/adbcontrol.dir/build: libadbcontrol.so

.PHONY : CMakeFiles/adbcontrol.dir/build

CMakeFiles/adbcontrol.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/adbcontrol.dir/cmake_clean.cmake
.PHONY : CMakeFiles/adbcontrol.dir/clean

CMakeFiles/adbcontrol.dir/depend:
	cd /home/wg/01_workspace/96tmpg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wg/01_workspace/96tmpg /home/wg/01_workspace/96tmpg /home/wg/01_workspace/96tmpg/build /home/wg/01_workspace/96tmpg/build /home/wg/01_workspace/96tmpg/build/CMakeFiles/adbcontrol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/adbcontrol.dir/depend

