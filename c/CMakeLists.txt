cmake_minimum_required(VERSION 4.0)
project(ttk91_compiler C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# creates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Googletest (aka gtest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# https://cmake.org/cmake/help/latest/module/FindBISON.html
find_package(BISON)
bison_target(
    ttk91_parser                        # name
    src/parser.bison                    # input .bison file
    src/parser.c                        # output .c
    DEFINES_FILE include/token.h        # output .h
    OPTIONS -Wall -t                    # options
)

find_package(FLEX)
flex_target(
    ttk91_scanner # name
    scanner.flex # input
    scanner.c # output
    OPTIONS --warn
)

set(SOURCES
    src/parser.c
    src/scanner.c
    src/program.c
    src/expr.c
    src/oper.c
    src/ttk_register.c
    src/label.c
    src/value.c
    src/comment.c
)

add_library(ttk91_compiler_lib ${SOURCES})
add_executable(ttk91_compiler src/main.c)

target_include_directories(ttk91_compiler       PRIVATE include)
target_include_directories(ttk91_compiler_lib   PRIVATE include)
target_link_libraries(ttk91_compiler ttk91_compiler_lib)


# Testing
enable_testing()

set(TESTING_SOURCES
    test/comment.cpp
    test/label.cpp
    test/value.cpp
    test/ttk_register.cpp
    test/oper.cpp
    test/expr.cpp
    ${SOURCES}
)

add_executable(tests ${TESTING_SOURCES})

target_link_libraries(
    tests
    GTest::gtest_main
)

target_include_directories(tests PRIVATE include)
include(GoogleTest)
gtest_discover_tests(tests)
