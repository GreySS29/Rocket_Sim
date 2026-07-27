cmake_minimum_required(VERSION 3.30)

project(Rock_sim)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/../../../openGL/glfw
    ${CMAKE_BINARY_DIR}/glfw-build
)

find_package(OpenGL REQUIRED)

add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/../../../openGL/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/../../../openGL/glad/include
)

add_library(Rock_core STATIC
    src/stage.cpp
    src/rocket.cpp
)

target_include_directories(Rock_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Rock_core PUBLIC
    glad
    glfw
    OpenGL::GL
)

add_executable(Rock_sim main_new.cpp)

target_link_libraries(Rock_sim PRIVATE
    Rock_core
)

target_compile_features(Rock_core PUBLIC cxx_std_23)

enable_testing()
add_subdirectory(tests)