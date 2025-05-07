cmake_minimum_required(VERSION 4.0)
project(ttk91_compiler C CXX)

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
    src/main.c
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

add_executable(ttk91_compiler ${SOURCES})

target_include_directories(ttk91_compiler PRIVATE include)
