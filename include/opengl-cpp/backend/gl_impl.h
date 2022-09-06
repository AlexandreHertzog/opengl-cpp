#pragma once

#include "gl.h"

namespace opengl_cpp {

class gl_impl_t : public gl_t {
  public:
    gl_impl_t() = default;
    ~gl_impl_t() override = default;

    gl_impl_t(const gl_impl_t &) = delete;
    gl_impl_t(gl_impl_t &&) = delete;
    gl_impl_t &operator=(gl_impl_t &&) = delete;
    gl_impl_t &operator=(const gl_impl_t &) = delete;

    // Allocators and deleters
    id_program_t new_program() override;
    id_shader_t new_shader(shader_type_t type) override;
    std::vector<id_buffer_t> new_buffers(size_t n) override;
    std::vector<id_texture_t> new_textures(size_t n) override;
    std::vector<id_vertex_array_t> new_vertex_arrays(size_t n) override;
    void destroy(size_t n, const id_buffer_t *buffers) override;
    void destroy(const id_program_t &program) override;
    void destroy(const id_shader_t &shader) override;
    void destroy(size_t n, const id_texture_t *textures) override;
    void destroy(size_t n, const id_vertex_array_t *arrays) override;

    // Texture functions
    void activate(const texture_t &tex) override;
    void bind(const texture_t &t) override;
    void generate_mipmap(const texture_t &t) override;
    void set_image(size_t width, size_t height, texture_format_t format, const unsigned char *data) override;
    void set_parameter(texture_parameter_t name, texture_parameter_values_t value) override;

    // Program functions
    void attach_shader(const program_t &p, const shader_t &s) override;
    std::string get_info_log(const program_t &p) override;
    int get_parameter(const program_t &p, program_parameter_t param) override;
    int get_uniform_location(const program_t &p, const char *name) override;
    void link(const program_t &p) override;
    void use(const program_t &p) override;
    void set_uniform(int location, float v0) override;
    void set_uniform(int location, int v0) override;
    void set_uniform(int location, const std::array<float, 3> &v) override;
    void set_uniform(int location, const std::array<float, 4> &v) override;
    void set_uniform(int location, const glm::vec3 &value) override;
    void set_uniform(int location, const glm::mat4 &value) override;

    // Buffer functions
    void bind(const buffer_t &b) override;
    void buffer_data(const buffer_t &b, size_t size, const void *data) override;

    // Vertex array functions
    void bind(const vertex_array_t &va) override;
    void enable_vertex_attrib_array(unsigned index) override;
    void vertex_attrib_pointer(unsigned index, size_t size, size_t stride, unsigned offset) override;

    // Shader functions
    error_t compile(const shader_t &s) override;
    std::string get_info_log(const shader_t &s) override;
    int get_parameter(const shader_t &s, shader_parameter_t param) override;
    void set_sources(const shader_t &s, size_t num_sources, const char **sources) override;

    void clear() override;
    void set_clear_color(const glm::vec4 &c) override;
    void disable(graphics_feature_t cap) override;
    void draw_arrays(int first, size_t count) override;
    void draw_elements(const std::vector<unsigned> &indices) override;
    void enable(graphics_feature_t cap) override;
    void polygon_mode(polygon_mode_t mode) override;
    void set_viewport(size_t width, size_t height) override;
};

} // namespace opengl_cpp
