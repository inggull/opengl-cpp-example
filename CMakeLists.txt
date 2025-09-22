cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(DEPS)
set(LIBS)

project(
    "OpenGL C++ Example"
    LANGUAGES C CXX
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/inggull/opengl-cpp-example.git
    DESCRIPTION "An OpenGL C++ Example"
)

message("[Compiler]")
message(" - Path : ${CMAKE_CXX_COMPILER}")
message(" - ID : ${CMAKE_CXX_COMPILER_ID}")
message(" - Version: ${CMAKE_CXX_COMPILER_VERSION}")

include(Dependency.cmake)
add_subdirectory(01_hello_window)
add_subdirectory(02_shader)