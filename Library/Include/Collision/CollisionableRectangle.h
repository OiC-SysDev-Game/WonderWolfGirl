#ifndef U22_COLLISION_COLLISIONABLE_RECTANGLE_H
#define U22_COLLISION_COLLISIONABLE_RECTANGLE_H


#include "../Shape/Rectangle.h"
#include "../Shape/Circle.h"
#include "RectangleCollisionDetector.h"

namespace u22::collision {
class CollisionableRectangle : public u22::shape::Rectangle {
    using super = u22::shape::Rectangle;
private:
    //! è’ìÀåüèo
    u22::collision::RectangleCollisionDetector _detector;
public:
    using u22::shape::Rectangle::Rectangle;

    operator super() {
        return super(left,top, right, bottom);
    }
    operator const super() const {
        return super(left, top, right, bottom);
    }
    CollisionableRectangle(const super& rectangle) {
        left = rectangle.left;
        top = rectangle.top;
        right = rectangle.right;
        bottom = rectangle.bottom;
    }
    CollisionableRectangle& operator=(const super& rectangle) {
        left = rectangle.left;
        top = rectangle.top;
        right = rectangle.right;
        bottom = rectangle.bottom;
        return *this;
    }

    bool CollisionRectangle(const super& target) const {
        return _detector.CollisionRectangle(*this, target);
    }
    bool CollisionCircle(const u22::shape::Circle& target) const {
        return _detector.CollisionCircle(*this, target);
    }
};
}
#endif // !U22_COLLISION_COLLISIONABLE_RECTANGLE_H