#pragma once

#include <gmock/gmock.h>
#include <opengl-cpp/backend/glfw.h>

namespace opengl_cpp::test {

class glfw_mock_t : public glfw_t {
    MOCK_METHOD(GLFWwindow *, create_window,
                (int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share), (override));
    MOCK_METHOD(void, destroy_window, (GLFWwindow * window), (override));
    MOCK_METHOD(int, init, (), (override));
    MOCK_METHOD(void, make_context_current, (GLFWwindow * window), (override));
    MOCK_METHOD(void, poll_events, (), (override));
    MOCK_METHOD(GLFWcursorposfun, set_cursor_pos_callback, (GLFWwindow * window, GLFWcursorposfun fun), (override));
    MOCK_METHOD(GLFWerrorfun, set_error_callback, (GLFWerrorfun callback), (override));
    MOCK_METHOD(GLFWframebuffersizefun, set_framebuffer_size_callback,
                (GLFWwindow * window, GLFWframebuffersizefun cbfun), (override));
    MOCK_METHOD(void, set_input_mode, (GLFWwindow * window, int mode, int value), (override));
    MOCK_METHOD(GLFWkeyfun, set_key_callback, (GLFWwindow * window, GLFWkeyfun cbfun), (override));
    MOCK_METHOD(void, set_window_should_close, (GLFWwindow * window, int value), (override));
    MOCK_METHOD(void, swap_buffers, (GLFWwindow * window), (override));
    MOCK_METHOD(void, terminate, (), (override));
    MOCK_METHOD(void, window_hint, (int hint, int value), (override));
    MOCK_METHOD(int, window_should_close, (GLFWwindow * window), (override));
};

} // namespace opengl_cpp::test
