#pragma once

#include "opengl-cpp/enumerates.h"
#include "opengl-cpp/identifier_t.h"
#include <array>
#include <glm/glm.hpp>
#include <string>

namespace opengl_cpp {

class buffer_t;
class texture_t;
class program_t;
class shader_t;
class texture_t;
class vertex_array_t;

class gl_t {
  public:
    gl_t() = default;
    virtual ~gl_t() = default;

    gl_t(const gl_t &) = delete;
    gl_t(gl_t &&) = delete;
    gl_t &operator=(const gl_t &) = delete;
    gl_t &operator=(gl_t &&) = delete;

    /**
     * @brief select active texture unit
     * @param tex Specifies which texture unit to make active. The number of texture units is implementation
     * dependent, but must be at least 80. texture must be one of GL_TEXTUREi, where i ranges from zero to the value of
     * GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS minus one. The initial value is GL_TEXTURE0.
     */
    virtual void activate(const texture_t &tex) = 0;

    /**
     * @brief Attaches a shader object to a program object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
     * @param p Specifies the program object to which a shader object will be attached.
     * @param s Specifies the shader object that is to be attached.
     */
    virtual void attach_shader(const program_t &p, const shader_t &s) = 0;

    /**
     * @brief bind a named buffer object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
     * @param b Specifies the name of a buffer object.
     */
    virtual void bind(const buffer_t &b) = 0;

    /**
     * @brief bind a named texture_coord to a texturing target
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindTexture.xhtml
     * @param t Texture to be bound.
     */
    virtual void bind(const texture_t &t) = 0;

    /**
     * @brief bind a vertex array object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
     * @param va Vertex array to be bound.
     */
    virtual void bind(const vertex_array_t &va) = 0;

    /**
     * @brief creates and initializes a buffer object's data store.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
     * @param b Buffer target
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param data Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no
     * data is to be copied.
     */
    virtual void buffer_data(const buffer_t &b, size_t size, const void *data) = 0;

    /**
     * @brief clear buffers to preset values.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClear.xhtml
     */
    virtual void clear() = 0;

    /**
     * @brief specify clear values for the color buffers.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml
     * @param c Specify the red, green, blue, and alpha values used when the color buffers are cleared. The initial
     * values are all 0.
     */
    virtual void set_clear_color(const glm::vec4 &c) = 0;

    /**
     * @brief Compiles a shader object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml
     * @param s Specifies the shader object to be compiled.
     */
    virtual error_t compile(const shader_t &s) = 0;

    /**
     * @brief Creates a program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
     * @return an empty program object and returns a non-zero value by which it can be referenced. A program object is
     * an object to which shader objects can be attached. This provides a mechanism to specify the shader objects that
     * will be linked to create a program. It also provides a means for checking the compatibility of the shaders that
     * will be used to create a program (for instance, checking the compatibility between a vertex shader and a fragment
     * shader). When no longer needed as part of a program object, shader objects can be detached.
     */
    virtual id_program_t new_program() = 0;

    /**
     * @brief Creates a shader object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
     * @param type Specifies the type of shader to be created. Must be one of GL_COMPUTE_SHADER,
     * GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
     * @return creates an empty shader object and returns a non-zero value by which it can be referenced. A shader
     * object is used to maintain the source code strings that define a shader. shader_type indicates the type of shader
     * to be created. Five types of shader are supported. A shader of type GL_COMPUTE_SHADER is a shader that is
     * intended to run on the programmable compute processor. A shader of type GL_VERTEX_SHADER is a shader that is
     * intended to run on the programmable vertex processor. A shader of type GL_TESS_CONTROL_SHADER is a shader that is
     * intended to run on the programmable tessellation processor in the control stage. A shader of type
     * GL_TESS_EVALUATION_SHADER is a shader that is intended to run on the programmable tessellation processor in the
     * evaluation stage. A shader of type GL_GEOMETRY_SHADER is a shader that is intended to run on the programmable
     * geometry processor. A shader of type GL_FRAGMENT_SHADER is a shader that is intended to run on the programmable
     * fragment processor.
     */
    virtual id_shader_t new_shader(shader_type_t type) = 0;

    /**
     * @brief generate buffer object names
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
     * @param n Specifies the number of buffer object names to be generated.
     * @return Generated buffer object.
     */
    virtual std::vector<id_buffer_t> new_buffers(size_t n) = 0;

    /**
     * @brief generate texture_coord names
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
     * @param n Specifies the number of texture_coord names to be generated.
     * @return Generated textures.
     */
    virtual std::vector<id_texture_t> new_textures(size_t n) = 0;

    /**
     * @brief generate vertex array object names
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
     * @param amount Specifies the number of vertex array object names to generate.
     * @return Vertex vector with indices.
     */
    [[nodiscard]] virtual std::vector<id_vertex_array_t> new_vertex_arrays(size_t amount) = 0;

    /**
     * @brief delete named buffer objects.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml
     * @param n Specifies the number of buffer objects to be deleted.
     * @param buffers Specifies an array of buffer objects to be deleted.
     */
    virtual void destroy(size_t n, const id_buffer_t *buffers) = 0;

    /**
     * @brief Deletes a program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml
     * @param program Specifies the program object to be deleted.
     */
    virtual void destroy(const id_program_t &program) = 0;

    /**
     * @brief Deletes a shader object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
     * @param shader Specifies the shader object to be deleted.
     */
    virtual void destroy(const id_shader_t &shader) = 0;

    /**
     * @brief delete named textures
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteTextures.xhtml
     * @param n Specifies the number of textures to be deleted.
     * @param textures Specifies an array of textures to be deleted.
     */
    virtual void destroy(size_t n, const id_texture_t *textures) = 0;

    /**
     * @brief delete vertex array objects.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml
     * @param n Specifies the number of vertex array objects to be deleted.
     * @param arrays Specifies the address of an array containing the n names of the objects to be deleted.
     */
    virtual void destroy(size_t n, const id_vertex_array_t *arrays) = 0;

    /**
     * @brief enable or disable server-side GL capabilities. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
     * @param cap Specifies a symbolic constant indicating a GL capability.
     */
    virtual void disable(graphics_feature_t cap) = 0;

    /**
     * @brief render primitives from array data. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
     * @param first Specifies the starting index in the enabled arrays.
     * @param count Specifies the number of indices to be rendered.
     */
    virtual void draw_arrays(int first, size_t count) = 0;

    /**
     * @brief render primitives from array data.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawElements.xhtml
     * @param indices Specifies a pointer to the location where the indices are stored.
     */
    virtual void draw_elements(const std::vector<unsigned> &indices) = 0;

    /**
     * @brief enable or disable server-side GL capabilities. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
     * @param cap Specifies a symbolic constant indicating a GL capability.
     */
    virtual void enable(graphics_feature_t cap) = 0;

    /**
     * @brief Enable or disable a generic vertex attribute array
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
     * @param index Specifies the index of the generic vertex attribute to be enabled or disabled.
     */
    virtual void enable_vertex_attrib_array(unsigned index) = 0;

    /**
     * @brief generate mipmaps for a specified texture_coord object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml
     * @param t Texture to have its mipmap generated.
     */
    virtual void generate_mipmap(const texture_t &t) = 0;

    /**
     * @brief Returns the information log for a program object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
     * @param p Specifies the program object whose information log is to be queried.
     * @return Information log.
     */
    virtual std::string get_info_log(const program_t &p) = 0;

    /**
     * @brief Returns the information log for a shader object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml
     * @param s Specifies the shader object whose information log is to be queried.
     * @return Information log.
     */
    virtual std::string get_info_log(const shader_t &s) = 0;

    /**
     * @brief Returns a parameter from a program object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
     * @param p Specifies the program object to be queried.
     * @param param Specifies the object parameter. Accepted symbolic names are GL_DELETE_STATUS, GL_LINK_STATUS,
     * GL_VALIDATE_STATUS, GL_INFO_LOG_LENGTH, GL_ATTACHED_SHADERS, GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
     * GL_ACTIVE_ATTRIBUTES, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, GL_ACTIVE_UNIFORMS, GL_ACTIVE_UNIFORM_BLOCKS,
     * GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, GL_ACTIVE_UNIFORM_MAX_LENGTH, GL_COMPUTE_WORK_GROUP_SIZE,
     * GL_PROGRAM_BINARY_LENGTH, GL_TRANSFORM_FEEDBACK_BUFFER_MODE, GL_TRANSFORM_FEEDBACK_VARYINGS,
     * GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, GL_GEOMETRY_VERTICES_OUT, GL_GEOMETRY_INPUT_TYPE, and
     * GL_GEOMETRY_OUTPUT_TYPE.
     * @return Requested object parameter.
     */
    virtual int get_parameter(const program_t &p, program_parameter_t param) = 0;

    /**
     * @brief Returns a parameter from a shader object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShader.xhtml
     * @param s Specifies the shader object to be queried.
     * @param param Specifies the object parameter. Accepted symbolic names are GL_SHADER_TYPE, GL_DELETE_STATUS,
     * GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH, GL_SHADER_SOURCE_LENGTH.
     * @return Requested object parameter.
     */
    virtual int get_parameter(const shader_t &s, shader_parameter_t param) = 0;

    /**
     * @brief Returns the location of a uniform variable
     * @param p Specifies the program object to be queried.
     * @param name Points to a null terminated string containing the name of the uniform variable whose location is to
     * be queried.
     * @return an integer that represents the location of a specific uniform variable within a program object.
     */
    virtual int get_uniform_location(const program_t &p, const char *name) = 0;

    /**
     * @brief Links a program object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
     * @param p Specifies the handle of the program object to be linked.
     */
    virtual error_t link(const program_t &p) = 0;

    /**
     * @brief select a polygon rasterization mode. See
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonMode.xhtml
     * @param mode Specifies how polygons will be rasterized. Accepted values are GL_POINT, GL_LINE, and GL_FILL. The
     * initial value is GL_FILL for both front- and back-facing polygons.
     */
    virtual void polygon_mode(polygon_mode_t mode) = 0;

    /**
     * @brief Replaces the source code in a shader object
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
     * @param shader Specifies the handle of the shader object whose source code is to be replaced.
     * @param num_sources Specifies the number of elements in the string and length arrays.
     * @param string Specifies an array of pointers to strings containing the source code to be loaded into the shader.
     */
    virtual void set_sources(const shader_t &s, size_t num_sources, const char **sources) = 0;

    /**
     * @brief specify a two-dimensional texture_coord image
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
     * @param width Specifies the width of the texture_coord image. All implementations support texture_coord images
     * that are at least 1024 texels wide.
     * @param height Specifies the height of the texture_coord image, or the number of layers in a texture_coord array,
     * in the case of the GL_TEXTURE_1D_ARRAY and GL_PROXY_TEXTURE_1D_ARRAY targets. All implementations support 2D
     * texture_coord images that are at least 1024 texels high, and texture_coord arrays that are at least 256 layers
     * deep.
     * @param format Specifies the format of the pixel data. The following symbolic values are accepted: GL_RED, GL_RG,
     * GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER,
     * GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void set_image(size_t width, size_t height, texture_format_t format, const unsigned char *data) = 0;

    /**
     * @brief set texture_coord parameters
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
     * @param name Specifies the symbolic name of a single-valued texture_coord parameter. pname can be one of the
following: GL_DEPTH_STENCIL_TEXTURE_MODE, GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_COMPARE_FUNC, GL_TEXTURE_COMPARE_MODE,
GL_TEXTURE_LOD_BIAS, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_MIN_LOD, GL_TEXTURE_MAX_LOD,
GL_TEXTURE_MAX_LEVEL, GL_TEXTURE_SWIZZLE_R, GL_TEXTURE_SWIZZLE_G, GL_TEXTURE_SWIZZLE_B, GL_TEXTURE_SWIZZLE_A,
GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, or GL_TEXTURE_WRAP_R. For the vector commands (glTexParameter*v), pname can also
be one of GL_TEXTURE_BORDER_COLOR or GL_TEXTURE_SWIZZLE_RGBA.
     * @param value For the scalar commands, specifies the value of pname.
     */
    virtual void set_parameter(texture_parameter_t name, texture_parameter_values_t value) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param v0 For the scalar commands, specifies the new values to be used for the specified uniform variable.
     */
    virtual void set_uniform(int location, float v0) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param v0 For the scalar commands, specifies the new values to be used for the specified uniform variable.
     */
    virtual void set_uniform(int location, int v0) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param v For the scalar commands, specifies the new values to be used for the specified uniform variable.
     */
    virtual void set_uniform(int location, const glm::vec3 &v) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param v For the scalar commands, specifies the new values to be used for the specified uniform variable.
     */
    virtual void set_uniform(int location, const std::array<float, 3> &v) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param v For the scalar commands, specifies the new values to be used for the specified uniform variable.
     */
    virtual void set_uniform(int location, const std::array<float, 4> &v) = 0;

    /**
     * @brief Specify the value of a uniform variable for the current program object.
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
     * @param location Specifies the location of the uniform variable to be modified.
     * @param count For the vector (glUniform*v) commands, specifies the number of elements that are to be modified.
     * This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array. For the
     * matrix (glUniformMatrix*) commands, specifies the number of matrices that are to be modified. This should be 1 if
     * the targeted uniform variable is not an array of matrices, and 1 or more if it is an array of matrices.
     * @param value For the vector and matrix commands, specifies a pointer to an array of count values that will be
     * used to update the specified uniform variable.
     */
    virtual void set_uniform(int location, const glm::mat4 &value) = 0;

    /**
     * @brief Installs a program object as part of current rendering state
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
     * @param program Specifies the handle of the program object whose executables are to be used as part of current
     * rendering state.
     */
    virtual void use(const program_t &p) = 0;

    /**
     * @brief define an array of generic vertex attribute data
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
     * @param index Specifies the index of the generic vertex attribute to be modified.
     * @param size Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally,
     * the symbolic constant GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.
     * @param stride Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the
     * generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
     * @param offset Specifies a offset of the first component of the first generic vertex attribute in the array in
     * the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
     */
    virtual void vertex_attrib_pointer(unsigned index, size_t size, size_t stride, unsigned offset) = 0;

    /**
     * @brief set the viewport
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml
     * @param width Specify the width and height of the viewport. When a GL context is first attached to a window, width
     * and height are set to the dimensions of that window.
     * @param height Specify the width and height of the viewport. When a GL context is first attached to a window,
     * width and height are set to the dimensions of that window.
     */
    virtual void set_viewport(size_t width, size_t height) = 0;
};

} // namespace opengl_cpp
