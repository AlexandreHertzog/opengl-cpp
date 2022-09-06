#include "gl_mock.h"

#include "opengl-cpp/buffer.h"
#include "gtest/gtest.h"

using ::testing::A;
using ::testing::Exactly;
using ::testing::Return;

using namespace opengl_cpp;       // NOLINT(google-build-using-namespace)
using namespace opengl_cpp::test; // NOLINT(google-build-using-namespace)

TEST(BufferTest, buildTwoElements) {
    const std::vector<id_buffer_t> ret = {1, 2};

    gl_mock_t gl;

    EXPECT_CALL(gl, new_buffers(2)).Times(Exactly(1)).WillOnce(Return(ret));
    EXPECT_CALL(gl, destroy(1, A<const id_buffer_t *>())).Times(Exactly(2));

    auto buffers = buffer_t::build(gl, 2);
    EXPECT_EQ(buffers.size(), 2);
    EXPECT_EQ(buffers[0].get_id(), ret[0]);
    EXPECT_EQ(buffers[1].get_id(), ret[1]);
}

TEST(BufferTest, buildZeroElements) {
    gl_mock_t gl;
    EXPECT_DEATH(buffer_t::build(gl, 0), "amount > 0");
}

TEST(BufferTest, buildDefault) {
    const std::vector<id_buffer_t> ret = {1};

    gl_mock_t gl;

    EXPECT_CALL(gl, new_buffers(1)).Times(Exactly(1)).WillOnce(Return(ret));
    EXPECT_CALL(gl, destroy(1, A<const id_buffer_t *>())).Times(Exactly(1));

    auto buffers = buffer_t(gl);
    EXPECT_EQ(buffers.get_id(), ret[0]);
}

TEST(BufferTest, moveConstructor) {
    gl_mock_t gl;
    buffer_t source(gl, 1, buffer_target_t::element_array);

    EXPECT_CALL(gl, new_buffers(A<size_t>())).Times(Exactly(0));
    EXPECT_CALL(gl, destroy(1, A<const id_buffer_t *>())).Times(Exactly(1));

    buffer_t dest(std::move(source));
    EXPECT_TRUE(dest.get_id());
    EXPECT_EQ(dest.get_target(), buffer_target_t::element_array);
    EXPECT_FALSE(source.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(source.get_target(), buffer_target_t::undefined);
}

TEST(BufferTest, moveAssignmentOperator) {
    gl_mock_t gl;
    buffer_t source(gl, 1, buffer_target_t::element_array);

    EXPECT_CALL(gl, new_buffers(A<size_t>())).Times(Exactly(0));
    EXPECT_CALL(gl, destroy(1, A<const id_buffer_t *>())).Times(Exactly(2));

    buffer_t dest(gl, 1);
    dest = std::move(source);
    EXPECT_TRUE(dest.get_id());
    EXPECT_EQ(dest.get_target(), buffer_target_t::element_array);
    EXPECT_FALSE(source.get_id()); // NOLINT(bugprone-use-after-move)
    EXPECT_EQ(source.get_target(), buffer_target_t::undefined);
}

TEST(BufferTest, bind) {
    gl_mock_t gl;

    EXPECT_CALL(gl, bind(A<const buffer_t &>())).Times(Exactly(1));
    EXPECT_CALL(gl, destroy(1, A<const id_buffer_t *>())).Times(Exactly(1));

    auto buffer = buffer_t(gl, 1, buffer_target_t::element_array);
    buffer.bind();
}
