#ifndef U22_COLLISION_RECTANGLE_COLLISION_DETECTOR_H
#define U22_COLLISION_RECTANGLE_COLLISION_DETECTOR_H


#include <cmath>

#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"


namespace u22::collision {
class RectangleCollisionDetector {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RectangleCollisionDetector();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~RectangleCollisionDetector();
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="a">矩形</param>
    /// <param name="b">矩形</param>
    /// <returns>衝突</returns>
    bool CollisionRectangle(const u22::shape::Rectangle& a, const u22::shape::Rectangle& b) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="a">矩形</param>
    /// <param name="b">円</param>
    /// <returns>衝突</returns>
    bool CollisionCircle(const u22::shape::Rectangle& rect, const u22::shape::Circle& circle) const;
};
}
#endif // !U22_COLLISION_RECTANGLE_COLLISION_DETECTOR_H