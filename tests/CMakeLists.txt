cmake_minimum_required(VERSION 3.30)

project(Rock_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Rock_sim_tests
    test_stage_launch.cpp
)

target_link_libraries(Rock_sim_tests PRIVATE Rock_core)

add_test(NAME Rock_sim_tests COMMAND Rock_sim_tests)

target_include_directories(Rock_sim_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)



