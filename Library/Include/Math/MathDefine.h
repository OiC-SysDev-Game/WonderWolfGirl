#ifndef U22_MATH_DEFINE_H
#define U22_MATH_DEFINE_H


#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"


namespace u22::math::def {
constexpr float kPi = 3.14192f;
constexpr float kHalfPi = kPi / 2.0f;
constexpr float kTwoPi = kPi * 2.0f;
}
namespace u22::math::vec2 {
constexpr auto kZero = u22::math::Vector2F(0.0f, 0.0f);
constexpr auto kOne = u22::math::Vector2F(1.0f, 1.0f);
constexpr auto kUnitX = u22::math::Vector2F(1.0f, 0.0f);
constexpr auto kUnitY = u22::math::Vector2F(0.0f, 1.0f);
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
constexpr auto kIdentity = glm::identity<glm::mat4x4>();
//constexpr u22::math::Matrix4x4F kIdentity = glm::identity<glm::mat4x4>();
//constexpr auto kIdentity = u22::math::Matrix4x4F::Identity();
}

namespace u22::math::utility {
constexpr float ToRadian(float degree) {
    return degree * (u22::math::def::kPi / 180.0f);
}
constexpr float ToDegree(float radian) {
    return radian * (180.0f / u22::math::def::kPi);
}
static u22::math::Matrix4x4F ConputeTransform(const u22::math::Vector3F& pos, const u22::math::Vector3F& rot, const u22::math::Vector3F& sca) {
    return 
        glm::translate(math::mat4x4::kIdentity, pos) * 
        glm::toMat4(glm::quat(rot)) * 
        glm::scale(math::mat4x4::kIdentity, sca);
}
}

namespace color::rgba {
constexpr auto kBlack = u22::math::Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
constexpr auto kRed = u22::math::Vector4F(1.0f, 0.0f, 0.0f, 1.0f);
constexpr auto kGreen = u22::math::Vector4F(0.0f, 1.0f, 0.0f, 1.0f);
constexpr auto kBlue = u22::math::Vector4F(0.0f, 0.0f, 1.0f, 1.0f);
constexpr auto kWhite = u22::math::Vector4F(1.0f, 1.0f, 1.0f, 1.0f);
}
#endif // !U22_MATH_DEFINE_H