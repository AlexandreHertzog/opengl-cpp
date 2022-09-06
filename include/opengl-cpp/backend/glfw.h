#pragma once

#include <GLFW/glfw3.h>

namespace opengl_cpp {

class glfw_t {
  public:
    glfw_t() = default;
    virtual ~glfw_t() = default;
    glfw_t(const glfw_t &) = delete;
    glfw_t(glfw_t &&) = delete;
    glfw_t &operator=(const glfw_t &) = delete;
    glfw_t &operator=(glfw_t &&) = delete;

    /**
     * @brief This function creates a window and its associated OpenGL or OpenGL ES context.
     * https://www.glfw.org/docs/3.3/group__window.html#ga3555a418df92ad53f917597fe2f64aeb
     * @param width The desired width, in screen coordinates, of the window. This must be greater than zero.
     * @param height The desired height, in screen coordinates, of the window. This must be greater than zero.
     * @param title The initial, UTF-8 encoded window title.
     * @param monitor The monitor to use for full screen mode, or NULL for windowed mode.
     * @param share The window whose context to share resources with, or NULL to not share resources.
     * @return The handle of the created window, or NULL if an error occurred.
     */
    virtual GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor,
                                           GLFWwindow *share) = 0;

    /**
     * @brief This function destroys the specified window and its context.
     * https://www.glfw.org/docs/3.3/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2
     * @param window The window to destroy.
     */
    virtual void destroy_window(GLFWwindow *window) = 0;

    /**
     * @brief This function initializes the GLFW library.
     * https://www.glfw.org/docs/3.3/group__init.html#ga317aac130a235ab08c6db0834907d85e
     * @return GLFW_TRUE if successful, or GLFW_FALSE if an error occurred.
     */
    virtual int init() = 0;

    /**
     * @brief This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread.
     * @param window The window whose context to make current, or NULL to detach the current context.
     */
    virtual void make_context_current(GLFWwindow *window) = 0;

    /**
     * @brief This function processes only those events that are already in the event queue and then returns
     * immediately. https://www.glfw.org/docs/3.3/group__window.html#ga37bd57223967b4211d60ca1a0bf3c832
     */
    virtual void poll_events() = 0;

    /**
     * @brief This function sets the cursor position callback of the specified window, which is called when the cursor
     * is moved.
     * @param window The window whose callback to set.
     * @param fun The new callback, or NULL to remove the currently set callback.
     */
    virtual GLFWcursorposfun set_cursor_pos_callback(GLFWwindow *window, GLFWcursorposfun fun) = 0;

    /**
     * @brief This function sets the error callback, which is called with an error code and a human-readable description
     * each time a GLFW error occurs. https://www.glfw.org/docs/3.3/group__init.html#gaff45816610d53f0b83656092a4034f40
     * @param callback The new callback, or NULL to remove the currently set callback.
     * @return The previously set callback, or NULL if no callback was set.
     */
    virtual GLFWerrorfun set_error_callback(GLFWerrorfun callback) = 0;

    /**
     * @brief This function sets the framebuffer resize callback of the specified window, which is called when the
     * framebuffer of the specified window is resized.
     * https://www.glfw.org/docs/3.0/group__window.html#ga3203461a5303bf289f2e05f854b2f7cf
     * @param window The window whose callback to set.
     * @param cbfun The new callback, or NULL to remove the currently set callback.
     * @return The previously set callback, or NULL if no callback was set or an error occurred.
     */
    virtual GLFWframebuffersizefun set_framebuffer_size_callback(GLFWwindow *window,
                                                                      GLFWframebuffersizefun cbfun) = 0;

    /**
     * @brief This function sets an input mode option for the specified window. See
     * https://www.glfw.org/docs/3.3/group__input.html#gaa92336e173da9c8834558b54ee80563b
     * @param window The window whose input mode to set.
     * @param mode One of GLFW_CURSOR, GLFW_STICKY_KEYS, GLFW_STICKY_MOUSE_BUTTONS, GLFW_LOCK_KEY_MODS or
     * GLFW_RAW_MOUSE_MOTION.
     * @param value The new value of the specified input mode.
     */
    virtual void set_input_mode(GLFWwindow *window, int mode, int value) = 0;

    /**
     * @brief This function sets the key callback of the specific window, which is called when a key is pressed,
     * repeated or released. https://www.glfw.org/docs/3.0/group__input.html#ga7e496507126f35ea72f01b2e6ef6d155
     * @param window The window whose callback to set.
     * @param cbfun The new key callback, or NULL to remove the currently set callback.
     * @return The previously set callback, or NULL if no callback was set or an error occurred.
     */
    virtual GLFWkeyfun set_key_callback(GLFWwindow *window, GLFWkeyfun cbfun) = 0;

    /**
     * @brief This function sets the value of the close flag of the specified window.
     * https://www.glfw.org/docs/3.3/group__window.html#ga49c449dde2a6f87d996f4daaa09d6708
     * @param window The window whose flag to change.
     * @param value The new value.
     */
    virtual void set_window_should_close(GLFWwindow *window, int value) = 0;

    /**
     * @brief This function swaps the front and back buffers of the specified window when rendering with OpenGL or
     * OpenGL ES. https://www.glfw.org/docs/3.3/group__window.html#ga15a5a1ee5b3c2ca6b15ca209a12efd14
     * @param window The window whose buffers to swap.
     */
    virtual void swap_buffers(GLFWwindow *window) = 0;

    /**
     * @brief This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any
     * other allocated resources. https://www.glfw.org/docs/3.3/group__init.html#gaaae48c0a18607ea4a4ba951d939f0901
     */
    virtual void terminate() = 0;

    /**
     * @brief This function sets hints for the next call to glfwCreateWindow.
     * https://www.glfw.org/docs/3.3/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033
     * @param hint The window hint to set.
     * @param value The new value of the window hint.
     */
    virtual void window_hint(int hint, int value) = 0;

    /**
     * @brief This function returns the value of the close flag of the specified window.
     * @param window The window to query.
     * @return The value of the close flag.
     */
    virtual int window_should_close(GLFWwindow *window) = 0;

    virtual void load_gl_loader() = 0;
};

} // namespace opengl_cpp
