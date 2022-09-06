include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(opengl_cpp_autotest src/test_buffer.cpp src/test_shader.cpp src/test_texture.cpp)
target_link_libraries(opengl_cpp_autotest PRIVATE opengl-cpp gmock gtest_main)
