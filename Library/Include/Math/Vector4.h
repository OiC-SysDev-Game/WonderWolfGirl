#ifndef U22_MATH_VECTOR4_H
#define U22_MATH_VECTOR4_H


#include "../Common/Common.h"


namespace u22::math {
template<typename T>
class Vector4 : public glm::vec4 {
    template<class> friend class Vector4;
public:
};

template<>
class Vector4<float> : public glm::vec4 {
    using super = glm::vec4;
public:
    using glm::vec4::vec4;

    operator super() {
        return super(x, y, z, w);
    }
    operator const super() const {
        return super(x, y, z, w);
    }
    Vector4(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    Vector4& operator=(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }
};
using Vector4F = Vector4<float>;
}
#endif // !U22_MATH_VECTOR4_H