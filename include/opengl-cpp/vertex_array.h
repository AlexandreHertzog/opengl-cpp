#pragma once

#include "buffer.h"
#include <ostream>
#include <vector>

namespace opengl_cpp {

struct vertex_t {
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_nor;
};

class vertex_array_t {
  public:
    /**
     * @brief Builds a large amount of vertex arrays at the same time.
     * @param amount Amount of vertex arrays.
     * @return Vector with the new vertex arrays.
     */
    static std::vector<vertex_array_t> build(gl_t &gl, size_t amount);

    /**
     * @brief Construct a new vertex_arrays object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
     *
     * @param size Number of vertex arrays to be generated.
     */
    explicit vertex_array_t(gl_t &gl, id_vertex_array_t id = 0);

    /**
     * @brief vertex_arrays move-constructor.
     *
     * @param other VectorArrays to be emptied.
     */
    vertex_array_t(vertex_array_t &&other) noexcept;

    vertex_array_t(const vertex_array_t &) = delete;
    vertex_array_t &operator=(const vertex_array_t &) = delete;

    /**
     * @brief Destroy the Vertex Arrays object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml
     *
     */
    ~vertex_array_t();

    /**
     * @brief vertex_arrays move-assignment operator.
     *
     * @param other vertex_arrays to be emptied.
     * @return vertex_arrays& Reference to this.
     */
    vertex_array_t &operator=(vertex_array_t &&other) noexcept;

    /**
     * @brief Binds the VertexArray object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
     *
     * @param index Index of the VertexArray to be bound.
     */
    void bind() const;

    /**
     * @brief Gets the ids associated with this vertex_array.
     * @return Vertex array ids.
     */
    [[nodiscard]] const id_vertex_array_t &get_id() const;

    /**
     * @brief Creates and initializes a buffer object data storage. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
     *
     * @param data Data to be stored.
     * @param usage Expected usage pattern of the data store.
     */
    void load(const std::vector<vertex_t> &vertices);

  private:
    gl_t &m_gl;
    id_vertex_array_t m_id;
    std::vector<buffer_t> m_buffers;

    void destroy();
};

std::ostream &operator<<(std::ostream &os, const opengl_cpp::vertex_array_t &va);

} // namespace opengl_cpp
