# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CLion 2023.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CLion 2023.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Workspace\github\ref_solution2cp_exercise\A

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/A.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/A.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/A.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A.dir/flags.make

CMakeFiles/A.dir/A8.c.obj: CMakeFiles/A.dir/flags.make
CMakeFiles/A.dir/A8.c.obj: D:/Workspace/github/ref_solution2cp_exercise/A/A8.c
CMakeFiles/A.dir/A8.c.obj: CMakeFiles/A.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/A.dir/A8.c.obj"
	"D:\Program Files\CLion 2023.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/A.dir/A8.c.obj -MF CMakeFiles\A.dir\A8.c.obj.d -o CMakeFiles\A.dir\A8.c.obj -c D:\Workspace\github\ref_solution2cp_exercise\A\A8.c

CMakeFiles/A.dir/A8.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/A.dir/A8.c.i"
	"D:\Program Files\CLion 2023.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Workspace\github\ref_solution2cp_exercise\A\A8.c > CMakeFiles\A.dir\A8.c.i

CMakeFiles/A.dir/A8.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/A.dir/A8.c.s"
	"D:\Program Files\CLion 2023.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Workspace\github\ref_solution2cp_exercise\A\A8.c -o CMakeFiles\A.dir\A8.c.s

# Object files for target A
A_OBJECTS = \
"CMakeFiles/A.dir/A8.c.obj"

# External object files for target A
A_EXTERNAL_OBJECTS =

A.exe: CMakeFiles/A.dir/A8.c.obj
A.exe: CMakeFiles/A.dir/build.make
A.exe: CMakeFiles/A.dir/linkLibs.rsp
A.exe: CMakeFiles/A.dir/objects1
A.exe: CMakeFiles/A.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable A.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\A.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A.dir/build: A.exe
.PHONY : CMakeFiles/A.dir/build

CMakeFiles/A.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\A.dir\cmake_clean.cmake
.PHONY : CMakeFiles/A.dir/clean

CMakeFiles/A.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Workspace\github\ref_solution2cp_exercise\A D:\Workspace\github\ref_solution2cp_exercise\A D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug D:\Workspace\github\ref_solution2cp_exercise\A\cmake-build-debug\CMakeFiles\A.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A.dir/depend

