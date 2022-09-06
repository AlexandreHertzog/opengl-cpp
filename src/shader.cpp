#include "shader.h"

#include <array>
#include <cassert>
#include <fstream>
#include <glad/glad.h>

namespace opengl_cpp {

shader_t::shader_t(gl_t &gl, shader_type_t type, const char *source) : m_gl(gl), m_id(gl.new_shader(type)) {
    if (source != nullptr) {
        compile(source, true);
    }
}

shader_t::shader_t(gl_t &gl, shader_type_t type, const std::filesystem::path &shader_path) : m_gl(gl) {
    std::ifstream shader_file(shader_path);
    if (!shader_file.is_open()) {
        throw std::runtime_error("shader file not found: " + shader_path.string());
    }

    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();

    std::string code = shader_stream.str();

    m_id = m_gl.new_shader(type);
    compile(code.c_str(), false);
}

shader_t::shader_t(shader_t &&other) noexcept : m_gl(other.m_gl) {
    if (m_id) {
        destroy();
    }
    m_id = std::move(other.m_id);
}

shader_t::~shader_t() {
    if (m_id) {
        destroy();
    }
}

shader_t &shader_t::operator=(shader_t &&other) noexcept {
    if (m_id) {
        destroy();
    }
    m_id = std::move(other.m_id);
    return *this;
}

const id_shader_t &shader_t::get_id() const {
    return m_id;
}

void shader_t::compile(const char *source, bool free_on_error) {
    assert(nullptr != source);
    assert(m_id);

    m_gl.set_sources(*this, 1, &source);

    const auto err = m_gl.compile(*this);
    if (error_t::no_error != err) {
        throw std::runtime_error("Error compiling shader: " + to_string(err));
    }

    const auto success = m_gl.get_parameter(*this, shader_parameter_t::compile_status);
    if (GL_FALSE == success) {
        const auto log = m_gl.get_info_log(*this);
        if (free_on_error) {
            destroy();
        }

        throw std::runtime_error(log);
    }
}

void shader_t::destroy() {
    assert(m_id);
    m_gl.destroy(m_id);
    m_id = 0;
}

std::ostream &operator<<(std::ostream &os, const opengl_cpp::shader_t &s) {
    return os << "shader(" << &s << " id=" << s.get_id();
}

} // namespace opengl_cpp
