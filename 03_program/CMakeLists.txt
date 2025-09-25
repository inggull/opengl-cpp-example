project(
    program
    LANGUAGES CXX
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/inggull/opengl-cpp-example.git
    DESCRIPTION "An OpenGL C++ Example"
)

message("[${PROJECT_NAME}]")

set(FILE_NAMES)
set(SRCS)

file(GLOB FILE_PATHS ${PROJECT_SOURCE_DIR}/src/*.cc)
foreach(FILE_PATH ${FILE_PATHS})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    list(APPEND FILE_NAMES ${FILE_NAME})
endforeach()

message(" - Source: ${FILE_NAMES}")

foreach(FILE_NAME ${FILE_NAMES})
    list(APPEND SRCS src/${FILE_NAME})
endforeach()

add_executable(${PROJECT_NAME} ${SRCS})
add_dependencies(${PROJECT_NAME} ${DEPS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/glad/include)
foreach(DEP ${DEPS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/_deps/${DEP}-src/include)
endforeach()
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()