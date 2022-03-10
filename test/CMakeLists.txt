cmake_minimum_required(VERSION 3.21)

set(ProjectTestName ExampleTests)

set(Sources
    ExampleTests.cpp
)

add_executable(${ProjectTestName} ${Sources})

target_link_libraries(
    ${ProjectTestName}
    PUBLIC ${CMAKE_PROJECT_NAME}_lib
    gtest_main
)

add_test(
    NAME ${ProjectTestName}
    COMMAND ${ProjectTestName}
)

