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
include CMakeFiles/ex-subgraph-planarizer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ex-subgraph-planarizer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ex-subgraph-planarizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex-subgraph-planarizer.dir/flags.make

CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o: CMakeFiles/ex-subgraph-planarizer.dir/flags.make
CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o: doc/examples/basic/subgraph-planarizer.cpp
CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o: CMakeFiles/ex-subgraph-planarizer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o -MF CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o.d -o CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o -c /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/subgraph-planarizer.cpp

CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/subgraph-planarizer.cpp > CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.i

CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/doc/examples/basic/subgraph-planarizer.cpp -o CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.s

# Object files for target ex-subgraph-planarizer
ex__subgraph__planarizer_OBJECTS = \
"CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o"

# External object files for target ex-subgraph-planarizer
ex__subgraph__planarizer_EXTERNAL_OBJECTS =

doc/examples/basic/ex-subgraph-planarizer: CMakeFiles/ex-subgraph-planarizer.dir/doc/examples/basic/subgraph-planarizer.cpp.o
doc/examples/basic/ex-subgraph-planarizer: CMakeFiles/ex-subgraph-planarizer.dir/build.make
doc/examples/basic/ex-subgraph-planarizer: libOGDF.a
doc/examples/basic/ex-subgraph-planarizer: libCOIN.a
doc/examples/basic/ex-subgraph-planarizer: CMakeFiles/ex-subgraph-planarizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable doc/examples/basic/ex-subgraph-planarizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex-subgraph-planarizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex-subgraph-planarizer.dir/build: doc/examples/basic/ex-subgraph-planarizer
.PHONY : CMakeFiles/ex-subgraph-planarizer.dir/build

CMakeFiles/ex-subgraph-planarizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex-subgraph-planarizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex-subgraph-planarizer.dir/clean

CMakeFiles/ex-subgraph-planarizer.dir/depend:
	cd /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF /home/thiagobastos/Downloads/ogdf.v2022.02/OGDF/CMakeFiles/ex-subgraph-planarizer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ex-subgraph-planarizer.dir/depend
