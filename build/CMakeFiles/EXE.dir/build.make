# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\B\Documents\DabEngine-cpp\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\B\Documents\DabEngine-cpp\build

# Include any dependencies generated for this target.
include CMakeFiles/EXE.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EXE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EXE.dir/flags.make

CMakeFiles/EXE.dir/Main.cpp.obj: CMakeFiles/EXE.dir/flags.make
CMakeFiles/EXE.dir/Main.cpp.obj: CMakeFiles/EXE.dir/includes_CXX.rsp
CMakeFiles/EXE.dir/Main.cpp.obj: C:/Users/B/Documents/DabEngine-cpp/src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\B\Documents\DabEngine-cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EXE.dir/Main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\EXE.dir\Main.cpp.obj -c C:\Users\B\Documents\DabEngine-cpp\src\Main.cpp

CMakeFiles/EXE.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EXE.dir/Main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\B\Documents\DabEngine-cpp\src\Main.cpp > CMakeFiles\EXE.dir\Main.cpp.i

CMakeFiles/EXE.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EXE.dir/Main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\B\Documents\DabEngine-cpp\src\Main.cpp -o CMakeFiles\EXE.dir\Main.cpp.s

# Object files for target EXE
EXE_OBJECTS = \
"CMakeFiles/EXE.dir/Main.cpp.obj"

# External object files for target EXE
EXE_EXTERNAL_OBJECTS =

C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: CMakeFiles/EXE.dir/Main.cpp.obj
C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: CMakeFiles/EXE.dir/build.make
C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: libDabEngine.a
C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: CMakeFiles/EXE.dir/linklibs.rsp
C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: CMakeFiles/EXE.dir/objects1.rsp
C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe: CMakeFiles/EXE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\B\Documents\DabEngine-cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:\Users\B\Documents\DabEngine-cpp\bin\EXE.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EXE.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EXE.dir/build: C:/Users/B/Documents/DabEngine-cpp/bin/EXE.exe

.PHONY : CMakeFiles/EXE.dir/build

CMakeFiles/EXE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\EXE.dir\cmake_clean.cmake
.PHONY : CMakeFiles/EXE.dir/clean

CMakeFiles/EXE.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\B\Documents\DabEngine-cpp\src C:\Users\B\Documents\DabEngine-cpp\src C:\Users\B\Documents\DabEngine-cpp\build C:\Users\B\Documents\DabEngine-cpp\build C:\Users\B\Documents\DabEngine-cpp\build\CMakeFiles\EXE.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EXE.dir/depend
