# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tylersmall/Documents/Connect-4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tylersmall/Documents/Connect-4/CMake

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CMake.app/Contents/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Applications/CMake.app/Contents/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/tylersmall/Documents/Connect-4/CMake/CMakeFiles /Users/tylersmall/Documents/Connect-4/CMake/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/tylersmall/Documents/Connect-4/CMake/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Connect_4

# Build rule for target.
Connect_4: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Connect_4
.PHONY : Connect_4

# fast build rule for target.
Connect_4/fast:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/build
.PHONY : Connect_4/fast

AI.o: AI.cpp.o

.PHONY : AI.o

# target to build an object file
AI.cpp.o:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/AI.cpp.o
.PHONY : AI.cpp.o

AI.i: AI.cpp.i

.PHONY : AI.i

# target to preprocess a source file
AI.cpp.i:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/AI.cpp.i
.PHONY : AI.cpp.i

AI.s: AI.cpp.s

.PHONY : AI.s

# target to generate assembly for a file
AI.cpp.s:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/AI.cpp.s
.PHONY : AI.cpp.s

Board.o: Board.cpp.o

.PHONY : Board.o

# target to build an object file
Board.cpp.o:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/Board.cpp.o
.PHONY : Board.cpp.o

Board.i: Board.cpp.i

.PHONY : Board.i

# target to preprocess a source file
Board.cpp.i:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/Board.cpp.i
.PHONY : Board.cpp.i

Board.s: Board.cpp.s

.PHONY : Board.s

# target to generate assembly for a file
Board.cpp.s:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/Board.cpp.s
.PHONY : Board.cpp.s

MainGame.o: MainGame.cpp.o

.PHONY : MainGame.o

# target to build an object file
MainGame.cpp.o:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/MainGame.cpp.o
.PHONY : MainGame.cpp.o

MainGame.i: MainGame.cpp.i

.PHONY : MainGame.i

# target to preprocess a source file
MainGame.cpp.i:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/MainGame.cpp.i
.PHONY : MainGame.cpp.i

MainGame.s: MainGame.cpp.s

.PHONY : MainGame.s

# target to generate assembly for a file
MainGame.cpp.s:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/MainGame.cpp.s
.PHONY : MainGame.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/Connect_4.dir/build.make CMakeFiles/Connect_4.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... Connect_4"
	@echo "... AI.o"
	@echo "... AI.i"
	@echo "... AI.s"
	@echo "... Board.o"
	@echo "... Board.i"
	@echo "... Board.s"
	@echo "... MainGame.o"
	@echo "... MainGame.i"
	@echo "... MainGame.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

