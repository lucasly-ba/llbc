cmake_minimum_required(VERSION 3.20)
project(gamblec VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(LLVM_LIBS
    core
    support
    irreader
    passes
    x86codegen
    x86asmparser
)

set(SOURCES
    src/ast.cpp
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/binder.cpp
    src/type_checker.cpp
    src/codegen.cpp
)

add_library(gamble_runtime STATIC
    runtime/runtime.cpp
)
target_include_directories(gamble_runtime PUBLIC runtime/)

add_executable(gamblec ${SOURCES})
set_target_properties(gamblec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(gamblec PRIVATE
    src/
    ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(gamblec PRIVATE
    ${LLVM_DEFINITIONS}
)

target_link_libraries(gamblec PRIVATE
    gamble_runtime
    ${LLVM_LIBS}
)

target_compile_options(gamblec PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-O0 -g -fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)

target_link_options(gamblec PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)

