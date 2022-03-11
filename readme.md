# A comprehensive framework for C++ development
- This CMake structure includes googletest as an external library using git submodule and organizes unittests in a separate executable
- Organizes codes on a separate src directory where headers and sources have corresponding headers and sources directory

## Packing installer
1. Build the code 
    - create a directory named 'build' with `mkdir build`
    - change to build directory with `cd build`
    - copy the configure.sh to build directory with `cp ../configure.sh .`
    - execute configure .sh with `./configure.sh`. You may need to change executable permission with `chmod +x configure.sh`
    - compile the code `make -j $(nproc)`. The  `$(nproc)` part of the code identifies the number of cpus and use all of them to compile the code.
2. From within the build directory issue `cpack` command to create installer. All the .sh, .tar.gz, and .tar.Z files are the installer in different format.

## Changing the name of the project
- Project name needs to be changed in two places
    1. Line #3 of the root directory CMakeLists.txt file `set(Project Project-Name)`. The 'Project-Name' can be changed to any appropriate name.
    2. Line #35 `PROJECT_NAME = "AM-CFD"` of the [Doxyfile.in](./documentation/Doxyfile.in) located in the *./documentation* directory. 

## Requirements
    - Doxygen 1.9.4