# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF

# Include any dependencies generated for this target.
include CMakeFiles/ex-manual.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ex-manual.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ex-manual.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex-manual.dir/flags.make

CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o: CMakeFiles/ex-manual.dir/flags.make
CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o: doc/examples/basic/manual.cpp
CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o: CMakeFiles/ex-manual.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o -MF CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o.d -o CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o -c /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/manual.cpp

CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/manual.cpp > CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.i

CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/manual.cpp -o CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.s

# Object files for target ex-manual
ex__manual_OBJECTS = \
"CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o"

# External object files for target ex-manual
ex__manual_EXTERNAL_OBJECTS =

doc/examples/basic/ex-manual: CMakeFiles/ex-manual.dir/doc/examples/basic/manual.cpp.o
doc/examples/basic/ex-manual: CMakeFiles/ex-manual.dir/build.make
doc/examples/basic/ex-manual: libOGDF.a
doc/examples/basic/ex-manual: libCOIN.a
doc/examples/basic/ex-manual: CMakeFiles/ex-manual.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable doc/examples/basic/ex-manual"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex-manual.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex-manual.dir/build: doc/examples/basic/ex-manual
.PHONY : CMakeFiles/ex-manual.dir/build

CMakeFiles/ex-manual.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex-manual.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex-manual.dir/clean

CMakeFiles/ex-manual.dir/depend:
	cd /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles/ex-manual.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ex-manual.dir/depend

