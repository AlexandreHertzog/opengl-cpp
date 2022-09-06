cmake_minimum_required(VERSION 3.22)

project(opengl-cpp VERSION 0.1.0 LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
add_subdirectory(lib)

add_library(opengl-cpp
        src/buffer.cpp
        src/gl_impl.cpp
        src/glfw_impl.cpp
        src/program.cpp
        src/shader.cpp
        src/texture.cpp
        src/vertex_array.cpp
        )

target_include_directories(opengl-cpp
        PUBLIC include
        PRIVATE include/opengl-cpp include/opengl-cpp/backend
        )

target_link_libraries(opengl-cpp PUBLIC glad glm PRIVATE glfw)
