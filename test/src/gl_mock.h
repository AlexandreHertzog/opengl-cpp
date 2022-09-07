#pragma once

#include <gmock/gmock.h>
#include <opengl-cpp/backend/gl.h>

namespace opengl_cpp::test {

class gl_mock_t : public opengl_cpp::gl_t {
  public:
    MOCK_METHOD(void, activate, (const texture_t &tex), (override));
    MOCK_METHOD(void, attach_shader, (const program_t &p, const shader_t &s), (override));
    MOCK_METHOD(void, bind, (const buffer_t &b), (override));
    MOCK_METHOD(void, bind, (const texture_t &t), (override));
    MOCK_METHOD(void, bind, (const vertex_array_t &va), (override));
    MOCK_METHOD(void, buffer_data, (const buffer_t &b, size_t size, const void *data), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, set_clear_color, (const glm::vec4 &c), (override));
    MOCK_METHOD(error_t, compile, (const shader_t &s), (override));
    MOCK_METHOD(id_program_t, new_program, (), (override));
    MOCK_METHOD(id_shader_t, new_shader, (shader_type_t type), (override));
    MOCK_METHOD(std::vector<id_buffer_t>, new_buffers, (size_t n), (override));
    MOCK_METHOD(std::vector<id_texture_t>, new_textures, (size_t n), (override));
    MOCK_METHOD(std::vector<id_vertex_array_t>, new_vertex_arrays, (size_t n), (override));
    MOCK_METHOD(void, destroy, (size_t n, const id_buffer_t *buffers), (override));
    MOCK_METHOD(void, destroy, (const id_program_t &program), (override));
    MOCK_METHOD(void, destroy, (const id_shader_t &shader), (override));
    MOCK_METHOD(void, destroy, (size_t n, const id_texture_t *textures), (override));
    MOCK_METHOD(void, destroy, (size_t n, const id_vertex_array_t *arrays), (override));
    MOCK_METHOD(void, disable, (graphics_feature_t cap), (override));
    MOCK_METHOD(void, draw_arrays, (int first, size_t count), (override));
    MOCK_METHOD(void, draw_elements, (const std::vector<unsigned> &indices), (override));
    MOCK_METHOD(void, enable, (graphics_feature_t cap), (override));
    MOCK_METHOD(void, enable_vertex_attrib_array, (unsigned index), (override));
    MOCK_METHOD(void, generate_mipmap, (const texture_t &t), (override));
    MOCK_METHOD(std::string, get_info_log, (const program_t &p), (override));
    MOCK_METHOD(std::string, get_info_log, (const shader_t &s), (override));
    MOCK_METHOD(int, get_parameter, (const program_t &p, program_parameter_t param), (override));
    MOCK_METHOD(int, get_parameter, (const shader_t &s, shader_parameter_t param), (override));
    MOCK_METHOD(int, get_uniform_location, (const program_t &p, const char *name), (override));
    MOCK_METHOD(error_t, link, (const program_t &p), (override));
    MOCK_METHOD(void, polygon_mode, (polygon_mode_t mode), (override));
    MOCK_METHOD(void, set_sources, (const shader_t &s, size_t num_sources, const char **sources), (override));
    MOCK_METHOD(void, set_image, (size_t width, size_t height, texture_format_t format, const unsigned char *data),
                (override));
    MOCK_METHOD(void, set_parameter, (texture_parameter_t name, texture_parameter_values_t value), (override));
    MOCK_METHOD(void, set_uniform, (int location, float v0), (override));
    MOCK_METHOD(void, set_uniform, (int location, int v0), (override));
    MOCK_METHOD(void, set_uniform, (int location, const glm::vec3 &v), (override));
    MOCK_METHOD(void, set_uniform, (int location, (const std::array<float, 3> &v)), (override));
    MOCK_METHOD(void, set_uniform, (int location, (const std::array<float, 4> &v)), (override));
    MOCK_METHOD(void, set_uniform, (int location, const glm::mat4 &value), (override));
    MOCK_METHOD(void, use, (const program_t &p), (override));
    MOCK_METHOD(void, vertex_attrib_pointer, (unsigned index, size_t size, size_t stride, unsigned offset), (override));
    MOCK_METHOD(void, set_viewport, (size_t width, size_t height), (override));
};

} // namespace opengl_cpp::test
