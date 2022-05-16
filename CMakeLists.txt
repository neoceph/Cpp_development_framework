cmake_minimum_required(VERSION 3.21)

set(Project AM-CFD)
set(ProjectLib ${Project}_lib)

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

include(CTest)
enable_testing()

# specifying the header directory
include_directories(
    ${ProjectLib} "${CMAKE_SOURCE_DIR}/src/headers"
    )
# setting the directory of the source for doxygen   
set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")

# specifying the directory where all the sources are located.
add_subdirectory(
    src
    )

add_subdirectory(
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

# setting up doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    message(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    message(${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT})
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )

else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)



# adding the googletest library separately as including the subdirectory with the previous command did not work!
add_subdirectory(
    extLibs/googletest EXCLUDE_FROM_ALL
    )


# CPack and git versioning stuffs

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#
# Make a version file containing the current version from git.
#
if(EXISTS "${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake")
  include("${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake")
else()
  include(GetGitRevisionDescription)
  git_describe(VERSION --tags --dirty=-dirty)
endif()

#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

# The following will transfer the version from git to the source package.
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${VERSION_SHORT}-Source")
#set(CPACK_INSTALL_COMMANDS "${CMAKE_SOURCE_DIR}/versionNumberToPackage.sh ${PROJECT_BINARY_DIR}/versionForSourcePackage.cmake \
#    ${PROJECT_BINARY_DIR}/_CPack_Packages/")


set(CPACK_INSTALL_COMMANDS "${CMAKE_COMMAND} -E make_directory \
    ${PROJECT_BINARY_DIR}/_CPack_Packages/Linux-Source/${CPACK_SOURCE_GENERATOR}/${CPACK_SOURCE_PACKAGE_FILE_NAME}/"
    "${CMAKE_COMMAND} -E copy \
    ${PROJECT_BINARY_DIR}/versionForSourcePackage.cmake \
    ${PROJECT_BINARY_DIR}/_CPack_Packages/Linux-Source/${CPACK_SOURCE_GENERATOR}/${CPACK_SOURCE_PACKAGE_FILE_NAME}/")
# Exclude the build and .git directory from the source package.
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_SOURCE_DIR}/.git/;${PROJECT_BINARY_DIR}/;${CPACK_SOURCE_IGNORE_FILES}")

include (CPack)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.cpp.in
                ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
configure_file(
   ${PROJECT_SOURCE_DIR}/versionForSourcePackage.cmake.in
   ${PROJECT_BINARY_DIR}/versionForSourcePackage.cmake @ONLY)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")

set(source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#Add the version_file to the project build.
# add_executable(${PROJECT_NAME} ${source_files} ${version_file})
# generating executable program by specifying the location of the file
add_executable(${Project} src/main.cpp ${version_file})

target_link_libraries(${Project} ${ProjectLib})

include(InstallRequiredSystemLibraries)
install(TARGETS ${Project})

# #set(CPACK_GENERATOR "DEB")
# set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Abdullah") # required

