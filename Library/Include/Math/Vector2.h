#ifndef U22_MATH_VECTOR2_H
#define U22_MATH_VECTOR2_H


#include "../Common/Common.h"


namespace u22::math {
template<typename T>
class Vector2 : public glm::vec2 {
    template<class> friend class Vector2;
public:
};

template<>
class Vector2<float> : public glm::vec2 {
    using super = glm::vec2;
public:
    using glm::vec2::vec2;

    operator super() {
        return super(x, y);
    }
    operator const super() const {
        return super(x, y);
    }
    Vector2(const super& v) {
        x = v.x;
        y = v.y;
    }
    Vector2& operator=(const super& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
};
template<>
class Vector2<int> : public glm::ivec2 {
    using super = glm::ivec2;
public:
    using glm::ivec2::ivec2;

    operator super() {
        return super(x, y);
    }
    operator const super() const {
        return super(x, y);
    }
    Vector2(const super& v) {
        x = v.x;
        y = v.y;
    }
    Vector2& operator=(const super& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
};

using Vector2I = Vector2<int>;
using Vector2F = Vector2<float>;
}
#endif // !U22_MATH_VECTOR3_H