cmake_minimum_required(VERSION 3.30)

project(Rock_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Rock_sim tests/test_stage_launch.cpp src/stage.cpp src/rocket.cpp)



target_include_directories(Rock_sim PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(Rock_sim PRIVATE cxx_std_23)