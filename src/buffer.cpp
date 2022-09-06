#include "buffer.h"

#include <cassert>

namespace opengl_cpp {

std::vector<buffer_t> buffer_t::build(gl_t &gl, size_t amount) {
    assert(amount > 0);

    const auto ids = gl.new_buffers(amount);

    std::vector<buffer_t> ret;
    ret.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        ret.emplace_back(gl, std::move(ids[i]));
    }
    return ret;
}

buffer_t::buffer_t(gl_t &gl, id_buffer_t id, buffer_target_t target) : m_gl(gl), m_target(target), m_id(std::move(id)) {
    if (!m_id) {
        m_id = std::move(m_gl.new_buffers(1)[0]);
    }
}

buffer_t::buffer_t(buffer_t &&other) noexcept : m_gl(other.m_gl), m_target(other.m_target) {
    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);
    other.m_target = buffer_target_t::undefined;
}

buffer_t::~buffer_t() {
    if (m_id) {
        destroy();
    }
}

buffer_t &buffer_t::operator=(buffer_t &&other) noexcept {
    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);

    m_target = other.m_target;
    other.m_target = buffer_target_t::undefined;
    return *this;
}

void buffer_t::bind() {
    assert(m_id);
    assert(buffer_target_t::undefined != m_target);
    m_gl.bind(*this);
}

const id_buffer_t &buffer_t::get_id() const {
    return m_id;
}

buffer_target_t buffer_t::get_target() const {
    return m_target;
}

void buffer_t::set_target(buffer_target_t target) {
    m_target = target;
}

void buffer_t::destroy() {
    assert(m_id);
    m_gl.destroy(1, &m_id);
    m_id = 0;
}

std::ostream &operator<<(std::ostream &os, const buffer_t &b) {
    return os << "buffer(" << &b << ") id=" << b.get_id() << ", target=" << static_cast<int>(b.get_target());
}

} // namespace opengl_cpp
