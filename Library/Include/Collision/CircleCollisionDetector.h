#ifndef U22_COLLISION_CIRCLE_COLLISION_DETECTOR_H
#define U22_COLLISION_CIRCLE_COLLISION_DETECTOR_H


#include <cmath>

#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"


namespace u22::collision {
class CircleCollisionDetector {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CircleCollisionDetector();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~CircleCollisionDetector();
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="a">円</param>
    /// <param name="b">円</param>
    /// <returns>衝突</returns>
    bool CollisionCircle(const u22::shape::Circle& a, const u22::shape::Circle& b) const;
};
}
#endif // !U22_COLLISION_CIRCLE_COLLISION_DETECTOR_H