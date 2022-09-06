#pragma once

#include <glad/glad.h>
#include <ostream>

namespace opengl_cpp {

enum class buffer_target_t {
    undefined = -1,
    simple_array = GL_ARRAY_BUFFER,
    element_array = GL_ELEMENT_ARRAY_BUFFER
};

enum class shader_type_t {
    undefined = -1,
    fragment = GL_FRAGMENT_SHADER,
    vertex = GL_VERTEX_SHADER
};

enum class shader_parameter_t {
    undefined = -1,
    compile_status = GL_COMPILE_STATUS
};

enum class texture_format_t {
    undefined = -1,
    rgb = GL_RGB,
    rgba = GL_RGBA
};

enum class program_parameter_t {
    undefined = -1,
    link_status = GL_LINK_STATUS
};

enum class texture_target_t {
    undefined = -1,
    tex_2d = GL_TEXTURE_2D
};

enum class texture_parameter_t {
    undefined = -1,
    mag_filter = GL_TEXTURE_MAG_FILTER,
    min_filter = GL_TEXTURE_MIN_FILTER,
    wrap_s = GL_TEXTURE_WRAP_S,
    wrap_t = GL_TEXTURE_WRAP_T,
};

enum class texture_parameter_values_t {
    undefined = -1,
    linear = GL_LINEAR,
    linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
    repeat = GL_REPEAT
};

enum class graphics_feature_t {
    undefined = -1,
    depth_test = GL_DEPTH_TEST,
};

enum class polygon_mode_t {
    undefined = -1,
    line = GL_LINE,
    fill = GL_FILL
};

enum class error_t {
    no_error = 0,
    invalid_enum = GL_INVALID_ENUM,
    invalid_value = GL_INVALID_VALUE,
    invalid_operation = GL_INVALID_OPERATION,
    invalid_framebuffer_operation = GL_INVALID_FRAMEBUFFER_OPERATION,
    out_of_memory = GL_OUT_OF_MEMORY,
};

inline std::ostream &operator<<(std::ostream &os, opengl_cpp::buffer_target_t t) {
    return os << std::hex << "0x" << static_cast<int>(t);
}

inline std::ostream &operator<<(std::ostream &os, opengl_cpp::texture_target_t t) {
    return os << std::hex << "0x" << static_cast<int>(t);
}

inline std::string to_string(error_t error) {
    return std::to_string(static_cast<int>(error));
}

} // namespace opengl_cpp
