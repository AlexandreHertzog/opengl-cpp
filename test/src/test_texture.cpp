#include "gl_mock.h"

#include "opengl-cpp/texture.h"
#include "gtest/gtest.h"

using testing::A;
using testing::Exactly;
using testing::Return;

using namespace opengl_cpp;       // NOLINT(google-build-using-namespace)
using namespace opengl_cpp::test; // NOLINT(google-build-using-namespace)

TEST(TextureTest, constructorGenerateTextures) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(1)).WillOnce(Return(ids));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t1(gl, unit, target);
    EXPECT_EQ(t1.get_id(), ids[0]);
}

TEST(TextureTest, constructorNoGenerateTextures) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(0));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t(gl, unit, target, ids[0]);
    EXPECT_EQ(t.get_id(), ids[0]);
}

TEST(TextureTest, constructorInvalidValues) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(0));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(0));

    std::unique_ptr<texture_t> t;
    EXPECT_DEATH(t.reset(new texture_t(gl, -1, target)), "0 <= unit"); // NOLINT(cppcoreguidelines-owning-memory)
}

TEST(TextureTest, moveConstructor) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(0));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t1(gl, unit, target, ids[0]);
    texture_t t2(std::move(t1));
    EXPECT_FALSE(t1.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(t1.get_target(), texture_target_t::undefined);
    EXPECT_EQ(t1.get_unit(), -1);
    EXPECT_EQ(t2.get_id(), ids[0]);
    EXPECT_EQ(t2.get_target(), target);
    EXPECT_EQ(t2.get_unit(), unit);
}

TEST(TextureTest, moveAssignmentOperator) {
    gl_mock_t gl;

    constexpr int unit1 = 1;
    constexpr int unit2 = 2;
    constexpr auto target1 = texture_target_t::tex_2d;
    constexpr auto target2 = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids1 = {5};
    const std::vector<id_texture_t> ids2 = {6};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(2)).WillOnce(Return(ids1)).WillOnce(Return(ids2));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(2));

    texture_t t1(gl, unit1, target1);
    texture_t t2(gl, unit2, target2);

    t2 = std::move(t1);

    EXPECT_FALSE(t1.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(t1.get_target(), texture_target_t::undefined);
    EXPECT_EQ(t1.get_unit(), -1);
    EXPECT_EQ(t2.get_id(), ids1[0]);
    EXPECT_EQ(t2.get_target(), target1);
    EXPECT_EQ(t2.get_unit(), unit1);
}

TEST(TextureTest, setParameter) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};
    constexpr auto parameter_name = texture_parameter_t::mag_filter;
    constexpr auto parameter_value = texture_parameter_values_t::linear;

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(1)).WillOnce(Return(ids));
    EXPECT_CALL(gl, activate(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, bind(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, set_parameter(parameter_name, parameter_value)).Times(Exactly(1));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t1(gl, unit, target);
    t1.bind();
    t1.set_parameter(parameter_name, parameter_value);
    EXPECT_EQ(t1.get_id(), ids[0]);
}

TEST(TextureTest, setImage) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};
    constexpr size_t width = 6;
    constexpr size_t height = 7;
    constexpr auto format = texture_format_t::rgba;
    const unsigned char data[] = {0x00, 0x01, 0x02}; // NOLINT(cppcoreguidelines-avoid-c-arrays)

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(1)).WillOnce(Return(ids));
    EXPECT_CALL(gl, activate(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, bind(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, set_image(width, height, format, static_cast<const unsigned char *>(data))).Times(Exactly(1));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t1(gl, unit, target);
    t1.bind();
    t1.set_image(width, height, format, static_cast<const unsigned char *>(data));
    EXPECT_EQ(t1.get_id(), ids[0]);
}

TEST(TextureTest, generateMipmap) {
    gl_mock_t gl;

    constexpr int unit = 1;
    constexpr auto target = texture_target_t::tex_2d;
    const std::vector<id_texture_t> ids = {3};

    EXPECT_CALL(gl, new_textures(1)).Times(Exactly(1)).WillOnce(Return(ids));
    EXPECT_CALL(gl, activate(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, bind(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, generate_mipmap(A<const texture_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, destroy(1, A<const id_texture_t *>())).Times(Exactly(1));

    texture_t t1(gl, unit, target);
    t1.bind();
    t1.generate_mipmap();
    EXPECT_EQ(t1.get_id(), ids[0]);
}
