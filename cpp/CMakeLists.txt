cmake_minimum_required(VERSION 4.0)
project(ttk91_compiler C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# creates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
    src/main.cpp
    src/Lexer.cpp
    src/Token.cpp
)

add_library(ttk91_compiler_lib ${SOURCES})
add_executable(ttk91_compiler src/main.cpp)

target_include_directories(ttk91_compiler       PRIVATE include)
target_include_directories(ttk91_compiler_lib   PRIVATE include)
target_link_libraries(ttk91_compiler ttk91_compiler_lib)
