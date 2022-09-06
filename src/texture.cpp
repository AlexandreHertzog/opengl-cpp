#include "texture.h"

namespace {

constexpr auto null_id = 0;
constexpr auto null_unit = -1;

} // namespace

namespace opengl_cpp {

texture_t::texture_t(gl_t &gl, int unit, texture_target_t target, id_texture_t id)
    : m_gl(gl), m_id(std::move(id)), m_target(target), m_unit(unit) {
    assert(0 <= unit);

    if (!m_id) {
        m_id = std::move(m_gl.new_textures(1)[0]);
    }
}

texture_t::texture_t(texture_t &&other) noexcept : m_gl(other.m_gl) {
    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);
    m_target = other.m_target;
    other.m_target = texture_target_t::undefined;
    m_unit = other.m_unit;
    other.m_unit = null_unit;
}

texture_t::~texture_t() {
    if (m_id) {
        destroy();
    }
}

texture_t &texture_t::operator=(texture_t &&other) noexcept {
    if (m_id) {
        destroy();
    }

    m_id = std::move(other.m_id);
    m_target = other.m_target;
    other.m_target = texture_target_t::undefined;
    m_unit = other.m_unit;
    other.m_unit = null_unit;
    return *this;
}

void texture_t::bind() {
    assert(m_id);
    assert(texture_target_t::undefined != m_target);
    assert(0 <= m_unit);

    m_gl.activate(*this);
    m_gl.bind(*this);
}

void texture_t::set_image(size_t width, size_t height, texture_format_t format, const unsigned char *data) {
    assert(m_id);
    assert(texture_target_t::undefined != m_target);

    m_gl.set_image(width, height, format, data);
}

void texture_t::generate_mipmap() {
    assert(m_id);
    assert(texture_target_t::undefined != m_target);
    m_gl.generate_mipmap(*this);
}

const id_texture_t &texture_t::get_id() const {
    return m_id;
}

texture_target_t texture_t::get_target() const {
    return m_target;
}

int texture_t::get_unit() const {
    return m_unit;
}

void texture_t::destroy() {
    assert(m_id);
    m_gl.destroy(1, &m_id);
    m_id = null_id;
    m_target = texture_target_t::undefined;
    m_unit = null_unit;
}

std::ostream &operator<<(std::ostream &os, const texture_t &t) {
    return os << "texture " << &t << " id=" << t.get_id() << " target=" << static_cast<int>(t.get_target())
              << " unit=" << t.get_unit();
}

} // namespace opengl_cpp