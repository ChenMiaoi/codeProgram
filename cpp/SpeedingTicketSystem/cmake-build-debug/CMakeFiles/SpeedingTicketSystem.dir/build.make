# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /home/zack/Application/clion-2022.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zack/Application/clion-2022.1.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SpeedingTicketSystem.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SpeedingTicketSystem.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SpeedingTicketSystem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpeedingTicketSystem.dir/flags.make

CMakeFiles/SpeedingTicketSystem.dir/main.cc.o: CMakeFiles/SpeedingTicketSystem.dir/flags.make
CMakeFiles/SpeedingTicketSystem.dir/main.cc.o: ../main.cc
CMakeFiles/SpeedingTicketSystem.dir/main.cc.o: CMakeFiles/SpeedingTicketSystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SpeedingTicketSystem.dir/main.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpeedingTicketSystem.dir/main.cc.o -MF CMakeFiles/SpeedingTicketSystem.dir/main.cc.o.d -o CMakeFiles/SpeedingTicketSystem.dir/main.cc.o -c /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/main.cc

CMakeFiles/SpeedingTicketSystem.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpeedingTicketSystem.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/main.cc > CMakeFiles/SpeedingTicketSystem.dir/main.cc.i

CMakeFiles/SpeedingTicketSystem.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpeedingTicketSystem.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/main.cc -o CMakeFiles/SpeedingTicketSystem.dir/main.cc.s

# Object files for target SpeedingTicketSystem
SpeedingTicketSystem_OBJECTS = \
"CMakeFiles/SpeedingTicketSystem.dir/main.cc.o"

# External object files for target SpeedingTicketSystem
SpeedingTicketSystem_EXTERNAL_OBJECTS =

SpeedingTicketSystem: CMakeFiles/SpeedingTicketSystem.dir/main.cc.o
SpeedingTicketSystem: CMakeFiles/SpeedingTicketSystem.dir/build.make
SpeedingTicketSystem: CMakeFiles/SpeedingTicketSystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SpeedingTicketSystem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpeedingTicketSystem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SpeedingTicketSystem.dir/build: SpeedingTicketSystem
.PHONY : CMakeFiles/SpeedingTicketSystem.dir/build

CMakeFiles/SpeedingTicketSystem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpeedingTicketSystem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpeedingTicketSystem.dir/clean

CMakeFiles/SpeedingTicketSystem.dir/depend:
	cd /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug /home/zack/code_work/github_work/My_Cpp_Programming/SpeedingTicketSystem/cmake-build-debug/CMakeFiles/SpeedingTicketSystem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpeedingTicketSystem.dir/depend

