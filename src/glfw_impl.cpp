#include <glad/glad.h>

#include "glfw_impl.h"

#include <iostream>
#include <stdexcept>

namespace opengl_cpp {

glfw_impl_t::glfw_impl_t()
    : m_error_fun([](int error_code, const char *description) {
          std::cerr << "GLFW error: error_code=" << error_code << ", description=\"" << description << "\"";
      }) {
    set_error_callback(m_error_fun);
    init();
}

glfw_impl_t::~glfw_impl_t() {
    glfwTerminate();
}

GLFWwindow *glfw_impl_t::create_window(int width, int height, const char *title, GLFWmonitor *monitor,
                                       GLFWwindow *share) {
    return glfwCreateWindow(width, height, title, monitor, share);
}

void glfw_impl_t::destroy_window(GLFWwindow *window) {
    glfwDestroyWindow(window);
}

int glfw_impl_t::init() {
    return glfwInit();
}

void glfw_impl_t::make_context_current(GLFWwindow *window) {
    glfwMakeContextCurrent(window);
}

void glfw_impl_t::poll_events() {
    glfwPollEvents();
}

GLFWcursorposfun glfw_impl_t::set_cursor_pos_callback(GLFWwindow *window, GLFWcursorposfun fun) {
    return glfwSetCursorPosCallback(window, fun);
}

GLFWerrorfun glfw_impl_t::set_error_callback(GLFWerrorfun callback) {
    return glfwSetErrorCallback(callback);
}

GLFWframebuffersizefun glfw_impl_t::set_framebuffer_size_callback(GLFWwindow *window, GLFWframebuffersizefun cbfun) {
    return glfwSetFramebufferSizeCallback(window, cbfun);
}

void glfw_impl_t::set_input_mode(GLFWwindow *window, int mode, int value) {
    glfwSetInputMode(window, mode, value);
}

GLFWkeyfun glfw_impl_t::set_key_callback(GLFWwindow *window, GLFWkeyfun cbfun) {
    return glfwSetKeyCallback(window, cbfun);
}

void glfw_impl_t::set_window_should_close(GLFWwindow *window, int value) {
    glfwSetWindowShouldClose(window, value);
}

void glfw_impl_t::swap_buffers(GLFWwindow *window) {
    glfwSwapBuffers(window);
}

void glfw_impl_t::terminate() {
    glfwTerminate();
}

void glfw_impl_t::window_hint(int hint, int value) {
    glfwWindowHint(hint, value);
}

int glfw_impl_t::window_should_close(GLFWwindow *window) {
    return glfwWindowShouldClose(window);
}

void glfw_impl_t::load_gl_loader() {
    if (0 == gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) { // NOLINT(*-reinterpret-cast)
        throw std::runtime_error("gladLoadGLLoader() failed");
    }
}

} // namespace opengl_cpp
