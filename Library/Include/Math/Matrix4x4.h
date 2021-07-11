#ifndef U22_MATH_MATRIX4X4_H
#define U22_MATH_MATRIX4X4_H


#include "../Common/Common.h"

#include <cstring>


namespace u22::math {
template<typename T>
class Matrix4x4 : public glm::mat4x4 {
    template<class> friend class Matrix4x4;
public:
};

template<>
class Matrix4x4 <float> : public glm::mat4x4 {
    using super = glm::mat4x4;
public:
    using glm::mat4x4::mat4x4;
    /// <summary>
    /// 名前付きコンストラクタ
    /// </summary>
    /// <returns></returns>
    //constexpr Matrix4x4 Identity() {
    static Matrix4x4 Identity() {
        return glm::identity<glm::mat4x4>();
    }
    Matrix4x4(const super& m) {
        std::memcpy(this, &m, sizeof(super));
    }
    Matrix4x4& operator=(const super& m) {
        std::memcpy(this, &m, sizeof(super));
        return *this;
    }
};
using Matrix4x4F = Matrix4x4<float>;
}
#endif // !U22_MATH_MATRIX4X4_H