cmake_minimum_required(VERSION 3.30)

project(Rock_sim)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MP_UNITS_API_CONTRACTS NONE CACHE STRING "")

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/../../openGL/glfw"
    "${CMAKE_BINARY_DIR}/glfw-build"
)

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/external/mp-units/src"
    "${CMAKE_BINARY_DIR}/mp-units-build"
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

set(IMGUI_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
)

add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/../../openGL/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/../../openGL/glad/include
)

add_library(Rock_core STATIC
    src/earth.cpp    
    src/stage.cpp
    src/rocket.cpp
    src/fabric.cpp
    src/launch_bay.cpp
    src/GUI/display.cpp
    src/GUI/rocket_render.cpp
    src/GUI/main_window.cpp
    src/Enviroment/atmosphere.cpp
    src/Panel/server.cpp
    
)

target_include_directories(Rock_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(Rock_core PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(Rock_core PUBLIC
    glad
    glfw
    OpenGL::GL
    OpenGL::GLU
    mp-units::mp-units
)


add_executable(Rock_sim 
    #tests/GUI_tests/main.cpp
    src/main.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
     ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
    
    
    )

target_link_libraries(Rock_sim PRIVATE
    Rock_core
    Boost::system
    Boost::thread
    dl
)

target_compile_features(Rock_core PUBLIC cxx_std_23)

enable_testing()
add_subdirectory(tests)