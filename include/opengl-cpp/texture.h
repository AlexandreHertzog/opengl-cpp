#pragma once

#include "opengl-cpp/backend/gl.h"
#include <cassert>
#include <filesystem>
#include <vector>

namespace opengl_cpp {

class texture_t {
  public:
    /**
     * @brief Creates a texture object with the given target and id. If ID is zero the texture is created. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
     * @param target OpenGL texture target.
     * @param id Texture ID.
     */
    explicit texture_t(gl_t &gl, int unit, texture_target_t target = texture_target_t::undefined, id_texture_t id = 0);

    /**
     * @brief Texture destructor. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteTextures.xhtml
     */
    ~texture_t();

    /**
     * @brief Texture move-constructor.
     * @param other Texture to be emptied.
     */
    texture_t(texture_t &&other) noexcept;

    /**
     * @brief Texture move-assignment operator.
     * @param other Texture to be emptied.
     * @return Reference to this.
     */
    texture_t &operator=(texture_t &&other) noexcept;

    texture_t(const texture_t &) = delete;
    texture_t &operator=(const texture_t &) = delete;

    /**
     * @brief Binds the texture in OpenGL. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindTexture.xhtml
     */
    void bind();

    /**
     * @brief Sets the texture image. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
     * @param width Specifies the width of the texture_coord image.
     * @param height Specifies the height of the texture_coord image.
     * @param format Specifies the format of the pixel data.
     * @param data Specifies a pointer to the image data in memory.
     */
    void set_image(size_t width, size_t height, texture_format_t format, const unsigned char *data);

    /**
     * @brief Generates the texture mipmap. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml
     */
    void generate_mipmap();

    /**
     * @brief Sets a texture parameter. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
     * @param param Parameter name.
     * @param value Parameter value.
     */
    template <class type_t> void set_parameter(texture_parameter_t param, type_t value) {
        assert(m_id);
        assert(m_target != texture_target_t::undefined);
        m_gl.set_parameter(param, value);
    }

    [[nodiscard]] const id_texture_t &get_id() const;
    [[nodiscard]] texture_target_t get_target() const;
    [[nodiscard]] int get_unit() const;

  private:
    gl_t &m_gl;
    id_texture_t m_id;
    texture_target_t m_target{};
    int m_unit{-1};

    void destroy();
};

std::ostream &operator<<(std::ostream &os, const texture_t &t);

} // namespace opengl_wrapper
