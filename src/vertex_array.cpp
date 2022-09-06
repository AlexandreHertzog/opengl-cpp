#include "vertex_array.h"

#include <cassert>

namespace opengl_cpp {

std::vector<vertex_array_t> vertex_array_t::build(gl_t &gl, size_t amount) {
    auto ids = gl.new_vertex_arrays(amount);

    std::vector<vertex_array_t> ret;
    ret.reserve(amount);
    for (auto &id : ids) {
        ret.emplace_back(gl, std::move(id));
    }
    return ret;
}

vertex_array_t::vertex_array_t(gl_t &gl, id_vertex_array_t id)
    : m_gl(gl), m_id(std::move(id)), m_buffers(buffer_t::build(gl, 2)) {

    if (!m_id) {
        m_id = std::move(m_gl.new_vertex_arrays(1)[0]);
    }

    assert(m_buffers.size() == 2);

    m_buffers[0].set_target(buffer_target_t::simple_array);
    m_buffers[1].set_target(buffer_target_t::element_array);
}

vertex_array_t::vertex_array_t(vertex_array_t &&other) noexcept
    : m_gl(other.m_gl), m_buffers(std::move(other.m_buffers)) {

    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);
}

vertex_array_t::~vertex_array_t() {
    if (m_id) {
        m_gl.destroy(1, &m_id);
    }
}

vertex_array_t &vertex_array_t::operator=(vertex_array_t &&other) noexcept {
    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);
    m_buffers = std::move(other.m_buffers);
    return *this;
}

void vertex_array_t::bind() const {
    assert(m_id);
    m_gl.bind(*this);
}

const id_vertex_array_t &vertex_array_t::get_id() const {
    return m_id;
}

void vertex_array_t::load(const std::vector<vertex_t> &vertices) {
    bind();

    m_buffers[0].bind();
    m_buffers[0].load(vertices);

    //    m_buffers[1].bind(); Disable as we don't support element drawing for now.
    //    m_buffers[1].load(indices);

    m_gl.vertex_attrib_pointer(0, 3, sizeof(vertex_t), 0);
    m_gl.enable_vertex_attrib_array(0);

    m_gl.vertex_attrib_pointer(1, 2, sizeof(vertex_t), sizeof(vertex_t::m_pos));
    m_gl.enable_vertex_attrib_array(1);

    m_gl.vertex_attrib_pointer(2, 3, sizeof(vertex_t), sizeof(vertex_t::m_pos) + sizeof(vertex_t::m_tex));
    m_gl.enable_vertex_attrib_array(2);
}

void vertex_array_t::destroy() {
    assert(m_id);
    m_gl.destroy(1, &m_id);
    m_id.clear();
}

std::ostream &operator<<(std::ostream &os, const opengl_cpp::vertex_array_t &va) {
    return os << "vertex_array(" << &va << ") id=" << va.get_id();
}

} // namespace opengl_cpp
