cmake_minimum_required(VERSION 3.30)

project(Rock_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Rock_core
    src/stage.cpp
    src/rocket.cpp
)

target_include_directories(Rock_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)



add_executable(Rock_sim main.cpp)
target_link_libraries(Rock_sim PRIVATE Rock_core)

target_compile_features(Rock_core PUBLIC cxx_std_23)
enable_testing()
add_subdirectory(tests)