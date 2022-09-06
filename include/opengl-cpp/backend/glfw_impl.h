#pragma once

#include "glfw.h"

namespace opengl_cpp {

class glfw_impl_t : public glfw_t {
  public:
    glfw_impl_t();
    ~glfw_impl_t() override;

    glfw_impl_t(const glfw_impl_t &) = delete;
    glfw_impl_t(glfw_impl_t &&) = delete;
    glfw_impl_t &operator=(const glfw_impl_t &) = delete;
    glfw_impl_t &operator=(glfw_impl_t &&) = delete;

    GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor,
                              GLFWwindow *share) override;
    void destroy_window(GLFWwindow *window) override;
    int init() override;
    void make_context_current(GLFWwindow *window) override;
    void poll_events() override;
    GLFWcursorposfun set_cursor_pos_callback(GLFWwindow *window, GLFWcursorposfun fun) override;
    GLFWerrorfun set_error_callback(GLFWerrorfun callback) override;
    GLFWframebuffersizefun set_framebuffer_size_callback(GLFWwindow *window, GLFWframebuffersizefun cbfun) override;
    void set_input_mode(GLFWwindow *window, int mode, int value) override;
    GLFWkeyfun set_key_callback(GLFWwindow *window, GLFWkeyfun cbfun) override;
    void set_window_should_close(GLFWwindow *window, int value) override;
    void swap_buffers(GLFWwindow *window) override;
    void terminate() override;
    void window_hint(int hint, int value) override;
    int window_should_close(GLFWwindow *window) override;
    void load_gl_loader() override;

  private:
    GLFWerrorfun m_error_fun;
};

} // namespace opengl_cpp
