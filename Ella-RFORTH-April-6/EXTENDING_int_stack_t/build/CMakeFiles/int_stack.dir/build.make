# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build

# Include any dependencies generated for this target.
include CMakeFiles/int_stack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/int_stack.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/int_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/int_stack.dir/flags.make

CMakeFiles/int_stack.dir/int_stack.c.o: CMakeFiles/int_stack.dir/flags.make
CMakeFiles/int_stack.dir/int_stack.c.o: /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/int_stack.c
CMakeFiles/int_stack.dir/int_stack.c.o: CMakeFiles/int_stack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/int_stack.dir/int_stack.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/int_stack.dir/int_stack.c.o -MF CMakeFiles/int_stack.dir/int_stack.c.o.d -o CMakeFiles/int_stack.dir/int_stack.c.o -c /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/int_stack.c

CMakeFiles/int_stack.dir/int_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/int_stack.dir/int_stack.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/int_stack.c > CMakeFiles/int_stack.dir/int_stack.c.i

CMakeFiles/int_stack.dir/int_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/int_stack.dir/int_stack.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/int_stack.c -o CMakeFiles/int_stack.dir/int_stack.c.s

# Object files for target int_stack
int_stack_OBJECTS = \
"CMakeFiles/int_stack.dir/int_stack.c.o"

# External object files for target int_stack
int_stack_EXTERNAL_OBJECTS =

int_stack: CMakeFiles/int_stack.dir/int_stack.c.o
int_stack: CMakeFiles/int_stack.dir/build.make
int_stack: CMakeFiles/int_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable int_stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/int_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/int_stack.dir/build: int_stack
.PHONY : CMakeFiles/int_stack.dir/build

CMakeFiles/int_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/int_stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/int_stack.dir/clean

CMakeFiles/int_stack.dir/depend:
	cd /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build /Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/EXTENDING_int_stack_t/build/CMakeFiles/int_stack.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/int_stack.dir/depend

