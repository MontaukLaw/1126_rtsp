# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marc/my_project/1126_rtsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marc/my_project/1126_rtsp/build

# Include any dependencies generated for this target.
include CMakeFiles/rtsp_demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rtsp_demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rtsp_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rtsp_demo.dir/flags.make

CMakeFiles/rtsp_demo.dir/src/main.c.o: CMakeFiles/rtsp_demo.dir/flags.make
CMakeFiles/rtsp_demo.dir/src/main.c.o: /home/marc/my_project/1126_rtsp/src/main.c
CMakeFiles/rtsp_demo.dir/src/main.c.o: CMakeFiles/rtsp_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/my_project/1126_rtsp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rtsp_demo.dir/src/main.c.o"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rtsp_demo.dir/src/main.c.o -MF CMakeFiles/rtsp_demo.dir/src/main.c.o.d -o CMakeFiles/rtsp_demo.dir/src/main.c.o -c /home/marc/my_project/1126_rtsp/src/main.c

CMakeFiles/rtsp_demo.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtsp_demo.dir/src/main.c.i"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/my_project/1126_rtsp/src/main.c > CMakeFiles/rtsp_demo.dir/src/main.c.i

CMakeFiles/rtsp_demo.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtsp_demo.dir/src/main.c.s"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/my_project/1126_rtsp/src/main.c -o CMakeFiles/rtsp_demo.dir/src/main.c.s

CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o: CMakeFiles/rtsp_demo.dir/flags.make
CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o: /home/marc/my_project/1126_rtsp/src/sample_common_isp.c
CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o: CMakeFiles/rtsp_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/my_project/1126_rtsp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o -MF CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o.d -o CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o -c /home/marc/my_project/1126_rtsp/src/sample_common_isp.c

CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.i"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marc/my_project/1126_rtsp/src/sample_common_isp.c > CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.i

CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.s"
	/opt/atk-dlrv1126-toolchain/usr/bin/arm-linux-gnueabihf-gcc --sysroot=/opt/atk-dlrv1126-toolchain/arm-buildroot-linux-gnueabihf/sysroot $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marc/my_project/1126_rtsp/src/sample_common_isp.c -o CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.s

# Object files for target rtsp_demo
rtsp_demo_OBJECTS = \
"CMakeFiles/rtsp_demo.dir/src/main.c.o" \
"CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o"

# External object files for target rtsp_demo
rtsp_demo_EXTERNAL_OBJECTS =

rtsp_demo: CMakeFiles/rtsp_demo.dir/src/main.c.o
rtsp_demo: CMakeFiles/rtsp_demo.dir/src/sample_common_isp.c.o
rtsp_demo: CMakeFiles/rtsp_demo.dir/build.make
rtsp_demo: CMakeFiles/rtsp_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marc/my_project/1126_rtsp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable rtsp_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtsp_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rtsp_demo.dir/build: rtsp_demo
.PHONY : CMakeFiles/rtsp_demo.dir/build

CMakeFiles/rtsp_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rtsp_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rtsp_demo.dir/clean

CMakeFiles/rtsp_demo.dir/depend:
	cd /home/marc/my_project/1126_rtsp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marc/my_project/1126_rtsp /home/marc/my_project/1126_rtsp /home/marc/my_project/1126_rtsp/build /home/marc/my_project/1126_rtsp/build /home/marc/my_project/1126_rtsp/build/CMakeFiles/rtsp_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rtsp_demo.dir/depend
