include(FetchContent)

add_subdirectory(glad)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
    GIT_SHALLOW 1
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(spdlog glfw)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(spdlog PRIVATE /utf-8)
    target_compile_options(glfw PRIVATE /utf-8)
endif()

list(APPEND DEPS spdlog glfw)
list(APPEND LIBS spdlog$<$<CONFIG:Debug>:d> glfw3)