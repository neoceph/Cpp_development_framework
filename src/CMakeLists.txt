set(Project ${CMAKE_PROJECT_NAME}_lib) # setting the library name

# specifying the project name
project(${Project})

# specifying the directory where header files are located
include_directories("/headers")

# selecting all the files with .cpp extension and assigning them to a variable 'SOURCES'
file(GLOB SOURCES "sources/*.cpp")

# adding to the library all the files that are selected and assigned to the variable name 'SOURCES'
add_library(
    ${Project} # Name of the project that is extracted from the root directory CMakeLists.txt
    ${SOURCES} # 
    )