#include "gl_mock.h"

#include "opengl-cpp/shader.h"
#include "gtest/gtest.h"

using testing::A;
using testing::Exactly;
using testing::Return;

using namespace opengl_cpp;       // NOLINT(google-build-using-namespace)
using namespace opengl_cpp::test; // NOLINT(google-build-using-namespace)

TEST(ShaderTest, constructCompileSuccessfull) {
    gl_mock_t gl;

    const char *source = "";
    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;

    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, set_sources(A<const shader_t &>(), 1, A<const char **>())).Times(Exactly(1));
    EXPECT_CALL(gl, compile(A<const shader_t &>())).Times(Exactly(1)).WillOnce(Return(opengl_cpp::error_t::no_error));
    EXPECT_CALL(gl, get_parameter(A<const shader_t &>(), shader_parameter_t::compile_status))
        .Times(Exactly(1))
        .WillOnce(Return(GL_TRUE));
    EXPECT_CALL(gl, destroy(id)).Times(Exactly(1));

    shader_t s(gl, type, source);
    EXPECT_EQ(s.get_id(), id);
}

TEST(ShaderTest, constructNoCompile) {
    gl_mock_t gl;

    const char *source = nullptr;
    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;

    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, destroy(id)).Times(Exactly(1));

    shader_t s(gl, type, source);
    EXPECT_EQ(s.get_id(), id);
}

TEST(ShaderTest, constructCompileFailed) {
    gl_mock_t gl;

    const char *source = "";
    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;

    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, set_sources(A<const shader_t &>(), 1, A<const char **>())).Times(Exactly(1));
    EXPECT_CALL(gl, compile(A<const shader_t &>())).Times(Exactly(1)).WillOnce(Return(opengl_cpp::error_t::no_error));
    EXPECT_CALL(gl, get_parameter(A<const shader_t &>(), shader_parameter_t::compile_status))
        .Times(Exactly(1))
        .WillOnce(Return(GL_FALSE));
    EXPECT_CALL(gl, get_info_log(A<const shader_t &>())).Times(Exactly(1)).WillOnce(Return("error string"));
    EXPECT_CALL(gl, destroy(id));

    std::unique_ptr<shader_t> s;
    EXPECT_THROW(s.reset(new shader_t(gl, type, source)), std::runtime_error); // NOLINT(*-owning-memory)
}

TEST(ShaderTest, moveConstructor) {
    gl_mock_t gl;

    const char *source = nullptr;
    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;

    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, destroy(id));

    shader_t s1(gl, type, source);
    shader_t s2(std::move(s1));

    EXPECT_FALSE(s1.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(s2.get_id(), id);
}

TEST(ShaderTest, moveAssignmentOperator) {
    gl_mock_t gl;

    const char *source = nullptr;
    const auto id1 = id_shader_t(1);
    const auto id2 = id_shader_t(2);
    constexpr auto type1 = shader_type_t::fragment;
    constexpr auto type2 = shader_type_t::vertex;

    EXPECT_CALL(gl, new_shader(type1)).Times(Exactly(1)).WillOnce(Return(id1));
    EXPECT_CALL(gl, new_shader(type2)).Times(Exactly(1)).WillOnce(Return(id2));
    EXPECT_CALL(gl, destroy(id1));
    EXPECT_CALL(gl, destroy(id2));

    shader_t s1(gl, type1, source);
    shader_t s2(gl, type2, source);

    s2 = std::move(s1);

    EXPECT_FALSE(s1.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(s2.get_id(), id1);
}

TEST(ShaderTest, constructFromPathSucceeded) {
    gl_mock_t gl;

    const std::filesystem::path file_name = "./shader.vert";

    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;
    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, set_sources(A<const shader_t &>(), 1, A<const char **>())).Times(Exactly(1));
    EXPECT_CALL(gl, compile(A<const shader_t &>())).Times(Exactly(1)).WillOnce(Return(opengl_cpp::error_t::no_error));
    EXPECT_CALL(gl, get_parameter(A<const shader_t &>(), shader_parameter_t::compile_status))
        .Times(Exactly(1))
        .WillOnce(Return(GL_TRUE));
    EXPECT_CALL(gl, destroy(id));

    shader_t s(gl, type, file_name);
    EXPECT_EQ(s.get_id(), id);
}

TEST(ShaderTest, constructFromPathCompileFail) {
    gl_mock_t gl;

    const std::filesystem::path file_name = "./shader.vert";

    const auto id = id_shader_t(123);
    constexpr auto type = shader_type_t::fragment;
    EXPECT_CALL(gl, new_shader(type)).Times(Exactly(1)).WillOnce(Return(id));
    EXPECT_CALL(gl, set_sources(A<const shader_t &>(), 1, A<const char **>())).Times(Exactly(1));
    EXPECT_CALL(gl, compile(A<const shader_t &>()))
        .Times(Exactly(1))
        .WillOnce(Return(opengl_cpp::error_t::invalid_operation));
    EXPECT_CALL(gl, destroy(id));

    std::unique_ptr<shader_t> s;
    EXPECT_THROW(s.reset(new shader_t(gl, type, file_name)), std::runtime_error); // NOLINT(*-owning-memory)
}
