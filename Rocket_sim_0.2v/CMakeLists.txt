cmake_minimum_required(VERSION 3.30)

project(Rock_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Rock_sim)

target_sources(Rock_sim
    PRIVATE
        main.cpp
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        gravity_temp.ixx
)

target_compile_features(Rock_sim PRIVATE cxx_std_23)