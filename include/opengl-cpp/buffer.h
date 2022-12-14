#pragma once

#include "opengl-cpp/backend/gl.h"
#include <ostream>
#include <vector>

namespace opengl_cpp {

class buffer_t {
  public:
    /**
     * @brief Builds a large amount of buffers at the same time.
     * @param amount Amount of buffers.
     * @return Vector with the new buffers.
     */
    static std::vector<buffer_t> build(gl_t &gl, size_t amount);

    /**
     * @brief Construct a new buffer object.
     *
     * @param id The buffer id.
     * @param target The buffer target.
     */
    explicit buffer_t(gl_t &gl, id_buffer_t id = 0, buffer_target_t target = buffer_target_t::undefined);

    /**
     * @brief buffer move-constructor.
     *
     * @param other buffer to be emptied.
     */
    buffer_t(buffer_t &&other) noexcept;

    buffer_t(const buffer_t &) = delete;
    buffer_t &operator=(const buffer_t &) = delete;

    /**
     * @brief Destroy the buffer object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml
     *
     */
    ~buffer_t();

    /**
     * @brief buffer move-assignment operator.
     *
     * @param other buffer to be emptied.
     * @return buffer& Reference to this.
     */
    buffer_t &operator=(buffer_t &&other) noexcept;

    /**
     * @brief Binds the indicated buffer object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
     */
    void bind();

    /**
     * @brief Creates and initializes a buffer object data storage. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
     *
     * @param data Data to be stored.
     * @param usage Expected usage pattern of the data store.
     */
    template <class type_t> void load(const std::vector<type_t> &data) {
        m_gl.buffer_data(*this, data.size() * sizeof(type_t), data.data());
    }

    /**
     * @brief Get the buffer ids associated with this object.
     * @return Buffer ids.
     */
    [[nodiscard]] const id_buffer_t &get_id() const;

    /**
     * @brief Gets the buffer target associated with this object.
     * @return Buffer target.
     */
    [[nodiscard]] buffer_target_t get_target() const;

    /**
     * @brief Sets the buffer target.
     * @param target Buffer target.
     */
    void set_target(buffer_target_t target);

  private:
    gl_t &m_gl;
    id_buffer_t m_id;
    buffer_target_t m_target;

    void destroy();
};

std::ostream &operator<<(std::ostream &s, const buffer_t &b);

} // namespace opengl_cpp
