# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build

# Include any dependencies generated for this target.
include CMakeFiles/LangCompare.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LangCompare.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LangCompare.dir/flags.make

CMakeFiles/LangCompare.dir/src/main.cpp.o: CMakeFiles/LangCompare.dir/flags.make
CMakeFiles/LangCompare.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LangCompare.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LangCompare.dir/src/main.cpp.o -c /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/main.cpp

CMakeFiles/LangCompare.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LangCompare.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/main.cpp > CMakeFiles/LangCompare.dir/src/main.cpp.i

CMakeFiles/LangCompare.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LangCompare.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/main.cpp -o CMakeFiles/LangCompare.dir/src/main.cpp.s

# Object files for target LangCompare
LangCompare_OBJECTS = \
"CMakeFiles/LangCompare.dir/src/main.cpp.o"

# External object files for target LangCompare
LangCompare_EXTERNAL_OBJECTS =

LangCompare: CMakeFiles/LangCompare.dir/src/main.cpp.o
LangCompare: CMakeFiles/LangCompare.dir/build.make
LangCompare: src/third_party/fmt/libfmt.a
LangCompare: CMakeFiles/LangCompare.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LangCompare"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LangCompare.dir/link.txt --verbose=$(VERBOSE)
	/usr/local/Cellar/cmake/3.18.4/bin/cmake -E copy_directory /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src

# Rule to build all files generated by this target.
CMakeFiles/LangCompare.dir/build: LangCompare

.PHONY : CMakeFiles/LangCompare.dir/build

CMakeFiles/LangCompare.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LangCompare.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LangCompare.dir/clean

CMakeFiles/LangCompare.dir/depend:
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2 /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2 /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles/LangCompare.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LangCompare.dir/depend

