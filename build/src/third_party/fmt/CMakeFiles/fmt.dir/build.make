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
include src/third_party/fmt/CMakeFiles/fmt.dir/depend.make

# Include the progress variables for this target.
include src/third_party/fmt/CMakeFiles/fmt.dir/progress.make

# Include the compile flags for this target's objects.
include src/third_party/fmt/CMakeFiles/fmt.dir/flags.make

src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.o: src/third_party/fmt/CMakeFiles/fmt.dir/flags.make
src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.o: ../src/third_party/fmt/src/format.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.o"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fmt.dir/src/format.cc.o -c /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/format.cc

src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fmt.dir/src/format.cc.i"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/format.cc > CMakeFiles/fmt.dir/src/format.cc.i

src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fmt.dir/src/format.cc.s"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/format.cc -o CMakeFiles/fmt.dir/src/format.cc.s

src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.o: src/third_party/fmt/CMakeFiles/fmt.dir/flags.make
src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.o: ../src/third_party/fmt/src/os.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.o"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fmt.dir/src/os.cc.o -c /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/os.cc

src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fmt.dir/src/os.cc.i"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/os.cc > CMakeFiles/fmt.dir/src/os.cc.i

src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fmt.dir/src/os.cc.s"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt/src/os.cc -o CMakeFiles/fmt.dir/src/os.cc.s

# Object files for target fmt
fmt_OBJECTS = \
"CMakeFiles/fmt.dir/src/format.cc.o" \
"CMakeFiles/fmt.dir/src/os.cc.o"

# External object files for target fmt
fmt_EXTERNAL_OBJECTS =

src/third_party/fmt/libfmt.a: src/third_party/fmt/CMakeFiles/fmt.dir/src/format.cc.o
src/third_party/fmt/libfmt.a: src/third_party/fmt/CMakeFiles/fmt.dir/src/os.cc.o
src/third_party/fmt/libfmt.a: src/third_party/fmt/CMakeFiles/fmt.dir/build.make
src/third_party/fmt/libfmt.a: src/third_party/fmt/CMakeFiles/fmt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libfmt.a"
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && $(CMAKE_COMMAND) -P CMakeFiles/fmt.dir/cmake_clean_target.cmake
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fmt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/third_party/fmt/CMakeFiles/fmt.dir/build: src/third_party/fmt/libfmt.a

.PHONY : src/third_party/fmt/CMakeFiles/fmt.dir/build

src/third_party/fmt/CMakeFiles/fmt.dir/clean:
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt && $(CMAKE_COMMAND) -P CMakeFiles/fmt.dir/cmake_clean.cmake
.PHONY : src/third_party/fmt/CMakeFiles/fmt.dir/clean

src/third_party/fmt/CMakeFiles/fmt.dir/depend:
	cd /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2 /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/src/third_party/fmt /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt /Volumes/Sierra/Users/mdkerr/Programming/Projects/LangCompareV2/build/src/third_party/fmt/CMakeFiles/fmt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/third_party/fmt/CMakeFiles/fmt.dir/depend

