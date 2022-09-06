#pragma once

#include "opengl-cpp/backend/gl.h"
#include <functional>
#include <ostream>
#include <vector>

namespace opengl_cpp {

class shader_t;

class program_t {
  public:
    /**
     * @brief Construct a new program object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
     *
     */
    program_t(gl_t &gl);

    /**
     * @brief program move-constructor.
     *
     * @param other program to be emptied.
     */
    program_t(program_t &&other) noexcept;

    /**
     * @brief Destroy the program object. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml
     *
     */
    ~program_t();

    program_t(const program_t &) = delete;
    program_t &operator=(const program_t &) = delete;

    /**
     * @brief program move-assignment operator.
     *
     * @param other program to be emptied.
     * @return program& Reference to this.
     */
    program_t &operator=(program_t &&other) noexcept;

    /**
     * @brief Equality comparison operator.
     * @param other program to be compared with.
     * @return `true` if the programs have the same id, `false` otherwise.
     */
    bool operator==(const program_t &other) const;

    /**
     * @brief Attaches a shader to the program. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
     *
     * @param shader Compiled shader to be attached.
     */
    void add_shader(shader_t shader);

    /**
     * @brief Links the program with the previously defined shaders. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
     *
     * @throws GlError When the link fails.
     */
    void link();

    /**
     * @brief Gets the reference for a Uniform variable in OpenGL. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml
     * @param var_name Variable name.
     * @return The variable reference.
     */
    int get_uniform_location(const char *var_name) const;

    template <class... type_t> void set_uniform(const char *var_name, const type_t &...t) {
        m_gl.set_uniform(get_uniform_location(var_name), t...);
    }

    template <class... type_t> void set_uniform(const std::string &var_name, const type_t &...t) {
        set_uniform(var_name.c_str(), t...);
    }

    /**
     * @brief Uses this program. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
     *
     */
    void use() const;

    /**
     * @brief Gets the program id.
     * @return Program id.
     */
    [[nodiscard]] const id_program_t &get_id() const;

  private:
    gl_t &m_gl;
    std::vector<shader_t> m_shaders;
    id_program_t m_id;

    void destroy();
};

std::ostream &operator<<(std::ostream &os, const program_t &p);

} // namespace opengl_cpp
