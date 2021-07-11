#ifndef U22_MATH_DEFINE_H
#define U22_MATH_DEFINE_H


#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"


namespace u22::math::def {
constexpr float kPi = 3.14192f;
}
namespace u22::math::vec3 {
constexpr auto kZero = u22::math::Vector3F(0.0f, 0.0f, 0.0f);
constexpr auto kOne = u22::math::Vector3F(1.0f, 1.0f, 1.0f);
constexpr auto kUnitX = u22::math::Vector3F(1.0f, 0.0f, 0.0f);
constexpr auto kUnitY = u22::math::Vector3F(0.0f, 1.0f, 0.0f);
constexpr auto kUnitZ = u22::math::Vector3F(0.0f, 0.0f, 1.0f);
}
namespace u22::math::vec4 {
constexpr auto kZero = u22::math::Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
constexpr auto kOne = u22::math::Vector4F(1.0f, 1.0f, 1.0f, 1.0f);
constexpr auto kUnitX = u22::math::Vector4F(1.0f, 0.0f, 0.0f, 0.0f);
constexpr auto kUnitY = u22::math::Vector4F(0.0f, 1.0f, 0.0f, 0.0f);
constexpr auto kUnitZ = u22::math::Vector4F(0.0f, 0.0f, 1.0f, 0.0f);
constexpr auto kUnitW = u22::math::Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
}

namespace u22::math::mat4x4 {
constexpr glm::mat4x4 kIdentity = glm::identity<glm::mat4x4>();
//constexpr auto kIdentity = u22::math::Matrix4x4F::Identity();
}

namespace color::rgba {
constexpr auto kRed = u22::math::Vector4F(1.0f, 0.0f, 0.0f, 1.0f);
constexpr auto kGreen = u22::math::Vector4F(0.0f, 1.0f, 0.0f, 1.0f);
constexpr auto kBlue = u22::math::Vector4F(0.0f, 0.0f, 1.0f, 1.0f);
}
#endif // !U22_MATH_DEFINE_H