#pragma once

#include <algorithm>

namespace opengl_cpp {

enum class identifier_type_t {
    buffer,
    shader,
    program,
    texture,
    vertex_arrays,
};

template <identifier_type_t id_type> class identifier_t {
  public:
    identifier_t(unsigned id = 0) : m_id(id) { // NOLINT(google-explicit-constructor)
    }

    identifier_t(identifier_t<id_type> &&other) noexcept { // NOLINT(cppcoreguidelines-pro-type-member-init)
        std::swap(m_id, other.m_id);
    }

    identifier_t &operator=(identifier_t &&other) noexcept {
        std::swap(m_id, other.m_id);
        other.m_id = 0;
        return *this;
    }

    ~identifier_t() = default;

    identifier_t(const identifier_t<id_type> &) = default;
    identifier_t &operator=(const identifier_t<id_type> &) = delete;

    operator bool() const {
        return m_id != 0;
    }

    operator unsigned() const {
        return m_id;
    }

    bool operator==(const identifier_t<id_type> &other) const {
        return m_id == other.m_id;
    }

    [[nodiscard]] unsigned get_id() const {
        return m_id;
    }

    void clear() {
        m_id = 0;
    }

  private:
    unsigned m_id;
};

using id_buffer_t = identifier_t<identifier_type_t::buffer>;
using id_shader_t = identifier_t<identifier_type_t::shader>;
using id_program_t = identifier_t<identifier_type_t::program>;
using id_texture_t = identifier_t<identifier_type_t::texture>;
using id_vertex_array_t = identifier_t<identifier_type_t::vertex_arrays>;

template <identifier_type_t id_type>
std::ostream &operator<<(std::ostream &os, const identifier_t<id_type> &id) {
    return os << id.get_id();
}

} // namespace opengl_cpp
