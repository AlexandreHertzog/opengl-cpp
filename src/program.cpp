#include "program.h"
#include "shader.h"

#include <algorithm>
#include <cassert>
#include <glad/glad.h>

namespace opengl_cpp {

program_t::program_t(gl_t &gl) : m_gl(gl), m_id(m_gl.new_program()) {
}

program_t::program_t(program_t &&other) noexcept
    : m_gl(other.m_gl), m_shaders(std::move(other.m_shaders)) {

    if (m_id) {
        destroy();
    }
    m_id = std::move(other.m_id);
}

program_t::~program_t() {
    if (m_id) {
        destroy();
    }
}

program_t &program_t::operator=(program_t &&other) noexcept {
    this->m_shaders = std::move(other.m_shaders);
    if (m_id) {
        destroy();
    }

    this->m_id = std::move(other.m_id);
    return *this;
}

bool program_t::operator==(const opengl_cpp::program_t &other) const {
    return this->m_id == other.m_id;
}

void program_t::add_shader(shader_t shader) {
    assert(m_id);

    m_gl.attach_shader(*this, shader);
    m_shaders.emplace_back(std::move(shader));
}

void program_t::link() {
    assert(m_id);

    m_gl.link(*this);

    const auto success = m_gl.get_parameter(*this, program_parameter_t::link_status);
    if (GL_FALSE == success) {
        throw std::runtime_error(m_gl.get_info_log(*this));
    }

    m_shaders.clear();
}

int program_t::get_uniform_location(const char *var_name) const {
    assert(m_id);
    return m_gl.get_uniform_location(*this, var_name);
}

void program_t::use() const {
    assert(m_id);
    m_gl.use(*this);
}

const id_program_t &program_t::get_id() const {
    return m_id;
}

void program_t::destroy() {
    assert(m_id);
    m_gl.destroy(m_id);
    m_id = 0;
}

std::ostream &operator<<(std::ostream &os, const opengl_cpp::program_t &p) {
    return os << "program(" << &p << ") id=" << p.get_id();
}

} // namespace opengl_cpp
