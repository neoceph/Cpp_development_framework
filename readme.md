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
- Sphinx 4.4.0
- Latexmk (required for pdf generation)
    - if not available can be installed with `sudo apt-get update -y` and next `sudo apt-get install -y latexmk`
    - for .sty file not found use `apt install texlive-latex-extra`

## generating documentation
- Under the build directory after a successful build `make docs` will generate api documentation under doc/api directory
    - in the doc/api/latex/ directory issuing `make pdf` will generate pdf from the generated latex files
- Under the doc/readthedocs directory issuing `make html` will generate html documentation under doc/readthedocs/_build/html directory
- `make latexpdf` will generate pdf documentation under doc/readthedocs/_build/latex directory

    