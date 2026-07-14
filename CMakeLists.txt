cmake_minimum_required(VERSION 3.20)
project(gblc VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

find_package(LLVM REQUIRED CONFIG)
find_package(CLI11 REQUIRED CONFIG)

llvm_map_components_to_libnames(LLVM_LIBS
    core
    support
    irreader
    passes
    x86codegen
    x86asmparser
)

set(SOURCES
    src/main.cpp
    src/ast/ast.cpp
    src/ast/dec.cpp
    src/ast/exp.cpp
    src/ast/stmt.cpp
    src/ast/type.cpp
    src/ast/print-ast.cpp
    src/ast/ast-visitor.cpp
    src/parse/lexer.cpp
    src/parse/parser.cpp
    src/parse/utils.cpp
    src/parse/factory.cpp
    src/bind/binder.cpp
    src/bind/scope.cpp
    src/type/type-checker.cpp
    src/gbir/value.cpp
    src/gbir/module.cpp
    src/gbir/top-level.cpp
    src/gbir/basic-block.cpp
    src/gbir/gbir-visitor.cpp
    src/gbir/print-gbir.cpp
    src/gbir/inst/const.cpp
    src/gbir/inst/binop.cpp
    src/gbir/inst/call.cpp
    src/gbir/inst/mem.cpp
    src/gbir/inst/phi.cpp
    src/gbir/inst/scene.cpp
    src/gbir/inst/enters.cpp
    src/gbir/inst/terminator.cpp
    src/gbir/inst/global.cpp
    src/gbir-gen/gbir-gen.cpp
    src/gbir-gen/factory.cpp
    src/llvm/codegen.cpp
)

add_library(runtime STATIC
    runtime/runtime.cpp
)
target_include_directories(runtime PUBLIC runtime/)

add_executable(gblc ${SOURCES})
set_target_properties(gblc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(gblc PRIVATE
    src/
    ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(gblc PRIVATE
    ${LLVM_DEFINITIONS}
)

target_link_libraries(gblc PRIVATE
    runtime
    CLI11::CLI11
    ${LLVM_LIBS}
)

target_compile_options(gblc PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-O0 -g -fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)

target_link_options(gblc PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)

