cmake_minimum_required(VERSION 3.21)

set(Project AM-CFD)
set(ProjectLib AM-CFD_lib)

project(${Project} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# check if openMP compilers are available and link them
find_package(OpenMP 4.0 REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

enable_testing()

# generating executable program by specifying the location of the file
add_executable(${Project} src/main.cpp)

# specifying the header directory
include_directories(
    ${ProjectLib} "${CMAKE_SOURCE_DIR}/src/headers"
    )

# specifying the directory where all the sources are located.
add_subdirectory(
    src
    test
    )

# adding git submodule chekout from the source

# Download all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# update submodules as needed
    option(GIT_SBUMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STSTUS "Submodule update")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
            )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# check all the submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extLibs/googletest/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodules was not downloaded! GIT_SUBMODULE is either turned off or failed. Please update submodules")
endif()

# adding the googletest library separately as including the subdirectory with the previous command did not work!
add_subdirectory(
    extLibs/googletest
    )
