#include "shader.h"

#include <array>
#include <cassert>
#include <fstream>
#include <glad/glad.h>

namespace opengl_cpp {

shader_t::shader_t(gl_t &gl, shader_type_t type, const char *source) : m_gl(gl), m_id(gl.new_shader(type)) {
    if (source != nullptr) {
        compile(source);
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
    compile(code.c_str());
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

void shader_t::compile(const char *source) {
    assert(nullptr != source);
    assert(m_id);

    m_gl.set_sources(*this, 1, &source);

    std::string error_message;

    const auto err = m_gl.compile(*this);
    if (error_t::no_error == err) {
        const auto success = m_gl.get_parameter(*this, shader_parameter_t::compile_status);
        if (GL_FALSE == success) {
            error_message = m_gl.get_info_log(*this);
            if (error_message.empty()) {
                error_message = "Shader compilation failed with unspecified error";
            }
        }
    } else {
        error_message = "Error compiling shader: " + to_string(err);
    }

    if (!error_message.empty()) {
        destroy();
        throw std::runtime_error(error_message);
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
