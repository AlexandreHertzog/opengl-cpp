#include "opengl-cpp/backend/gl_impl.h"

#include "buffer.h"
#include "program.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include <glm/gtc/type_ptr.hpp>

namespace opengl_cpp {

void gl_impl_t::activate(const texture_t &tex) {
    glActiveTexture(tex.get_unit() + GL_TEXTURE0);
}

void gl_impl_t::attach_shader(const program_t &p, const shader_t &s) {
    glAttachShader(p.get_id(), s.get_id());
}

void gl_impl_t::bind(const buffer_t &b) {
    glBindBuffer(static_cast<GLenum>(b.get_target()), b.get_id());
}

void gl_impl_t::bind(const texture_t &t) {
    glBindTexture(static_cast<GLenum>(t.get_target()), t.get_id());
}

void gl_impl_t::bind(const vertex_array_t &va) {
    glBindVertexArray(va.get_id());
}

void gl_impl_t::buffer_data(const buffer_t &b, size_t size, const void *data) {
    glBufferData(static_cast<GLenum>(b.get_target()), size, data, GL_STATIC_DRAW);
}

void gl_impl_t::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_impl_t::set_clear_color(const glm::vec4 &c) {
    glClearColor(c[0], c[1], c[2], c[3]);
}

error_t gl_impl_t::compile(const shader_t &s) {
    glCompileShader(s.get_id());
    return static_cast<error_t>(glGetError());
}

identifier_t<identifier_type_t::program> gl_impl_t::new_program() {
    return glCreateProgram();
}

identifier_t<identifier_type_t::shader> gl_impl_t::new_shader(shader_type_t type) {
    return glCreateShader(static_cast<GLenum>(type));
}

void gl_impl_t::destroy(size_t n, const identifier_t<identifier_type_t::buffer> *buffers) {
    std::vector<unsigned> to_delete(n);
    for (int i = 0; i < n; i++) {
        to_delete[i] = buffers[i].get_id();
    }
    glDeleteBuffers(n, to_delete.data());
}

void gl_impl_t::destroy(const id_program_t &program) {
    glDeleteProgram(program.get_id());
}

void gl_impl_t::destroy(const id_shader_t &shader) {
    glDeleteShader(shader.get_id());
}

void gl_impl_t::destroy(size_t n, const id_texture_t *textures) {
    std::vector<unsigned> to_delete(n);
    for (int i = 0; i < n; i++) {
        to_delete[i] = textures[i].get_id();
    }
    glDeleteTextures(n, to_delete.data());
}

void gl_impl_t::destroy(size_t n, const id_vertex_array_t *arrays) {
    std::vector<unsigned> to_delete(n);
    for (int i = 0; i < n; i++) {
        to_delete[i] = arrays[i].get_id();
    }
    glDeleteVertexArrays(n, to_delete.data());
}

void gl_impl_t::disable(graphics_feature_t cap) {
    glDisable(static_cast<GLenum>(cap));
}

void gl_impl_t::draw_arrays(int first, size_t count) {
    glDrawArrays(GL_TRIANGLES, first, count);
}

void gl_impl_t::draw_elements(const std::vector<unsigned> &indices) {
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void gl_impl_t::enable(graphics_feature_t cap) {
    glEnable(static_cast<GLenum>(cap));
}

void gl_impl_t::enable_vertex_attrib_array(unsigned index) {
    glEnableVertexAttribArray(index);
}

std::vector<id_buffer_t> gl_impl_t::new_buffers(size_t n) {
    std::vector<GLuint> ids(n);
    glGenBuffers(n, ids.data());

    std::vector<id_buffer_t> ret;
    ret.reserve(n);
    for (const auto to_ret : ids) {
        ret.emplace_back(to_ret);
    }
    return ret;
}

std::vector<id_texture_t> gl_impl_t::new_textures(size_t n) {
    std::vector<GLuint> ids(n);
    glGenTextures(n, ids.data());

    std::vector<id_texture_t> ret;
    ret.reserve(n);
    for (const auto to_ret : ids) {
        ret.emplace_back(to_ret);
    }
    return ret;
}

std::vector<id_vertex_array_t> gl_impl_t::new_vertex_arrays(size_t n) {
    std::vector<GLuint> ids(n);
    glGenVertexArrays(n, ids.data());

    std::vector<id_vertex_array_t> ret;
    ret.reserve(n);
    for (const auto to_ret : ids) {
        ret.emplace_back(to_ret);
    }
    return ret;
}

void gl_impl_t::generate_mipmap(const texture_t &t) {
    glGenerateMipmap(static_cast<GLenum>(t.get_target()));
}

std::string gl_impl_t::get_info_log(const program_t &p) {
    GLint info_log_len = 0;
    glGetProgramiv(p.get_id(), GL_INFO_LOG_LENGTH, &info_log_len);

    std::string info_log;
    info_log.reserve(info_log_len);
    glGetProgramInfoLog(p.get_id(), info_log_len, nullptr, info_log.data());
    return info_log;
}

int gl_impl_t::get_parameter(const program_t &p, program_parameter_t param) {
    int ret = 0;
    glGetProgramiv(p.get_id(), static_cast<GLenum>(param), &ret);
    return ret;
}

std::string gl_impl_t::get_info_log(const shader_t &s) {
    GLint info_log_len = 0;
    glGetShaderiv(s.get_id(), GL_INFO_LOG_LENGTH, &info_log_len);

    std::string info_log;
    info_log.reserve(info_log_len);
    glGetShaderInfoLog(s.get_id(), info_log_len, nullptr, info_log.data());
    return info_log;
}

int gl_impl_t::get_parameter(const shader_t &s, shader_parameter_t param) {
    int ret = 0;
    glGetShaderiv(s.get_id(), static_cast<GLenum>(param), &ret);
    return ret;
}

int gl_impl_t::get_uniform_location(const program_t &p, const char *name) {
    return glGetUniformLocation(p.get_id(), name);
}

error_t gl_impl_t::link(const program_t &p) {
    glLinkProgram(p.get_id());
    return static_cast<error_t>(glGetError());
}

void gl_impl_t::polygon_mode(polygon_mode_t mode) {
    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
}

void gl_impl_t::set_sources(const shader_t &s, size_t num_sources, const char **sources) {
    glShaderSource(s.get_id(), num_sources, sources, nullptr);
}

void gl_impl_t::set_image(size_t width, size_t height, texture_format_t format, const unsigned char *data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, static_cast<GLenum>(format), GL_UNSIGNED_BYTE, data);
}

void gl_impl_t::set_parameter(texture_parameter_t name, texture_parameter_values_t value) {
    glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(name), static_cast<GLint>(value));
}

void gl_impl_t::set_uniform(int location, float v0) {
    glUniform1f(location, v0);
}

void gl_impl_t::set_uniform(int location, GLint v0) {
    glUniform1i(location, v0);
}

void gl_impl_t::set_uniform(int location, const std::array<float, 3> &v) {
    glUniform3f(location, v[0], v[1], v[2]);
}

void gl_impl_t::set_uniform(int location, const glm::vec3 &v) {
    glUniform3f(location, v[0], v[1], v[2]);
}

void gl_impl_t::set_uniform(int location, const std::array<float, 4> &v) {
    glUniform4f(location, v[0], v[1], v[2], v[3]);
}

void gl_impl_t::set_uniform(int location, const glm::mat4 &value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void gl_impl_t::use(const program_t &p) {
    glUseProgram(p.get_id());
}

void gl_impl_t::vertex_attrib_pointer(unsigned index, size_t size, size_t stride, unsigned offset) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>(offset));
}

void gl_impl_t::set_viewport(size_t width, size_t height) {
    glViewport(0, 0, width, height);
}

} // namespace opengl_cpp