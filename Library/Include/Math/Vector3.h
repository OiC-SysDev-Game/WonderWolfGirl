#ifndef U22_MATH_VECTOR3_H
#define U22_MATH_VECTOR3_H


#include "../Common/Common.h"

#include "Vector2.h"


namespace u22::math {
template<typename T>
class Vector3 : public glm::vec3 {
    template<class> friend class Vector3;
public:
};

template<>
class Vector3<float> : public glm::vec3 {
    using super = glm::vec3;
public:
    using glm::vec3::vec3;

    operator super() {
        return super(x, y, z);
    }
    operator const super() const {
        return super(x, y, z);
    }
    Vector3(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vector3& operator=(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }


    Vector3(const Vector2<float>& v) {
        x = v.x;
        y = v.y;
        z = 0.0f;
    }
    Vector3& operator=(const Vector2<float>& v) {
        x = v.x;
        y = v.y;
        z = 0.0f;
        return *this;
    }

};
template<>
class Vector3<int> : public glm::ivec3 {
    using super = glm::ivec3;
public:
    using glm::ivec3::ivec3;

    operator super() {
        return super(x, y, z);
    }
    operator const super() const {
        return super(x, y, z);
    }
    Vector3(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vector3& operator=(const super& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
};

using Vector3I = Vector3<int>;
using Vector3F = Vector3<float>;
}
#endif // !U22_MATH_VECTOR3_H