#ifndef U22_COLLISION_COLLISIONABLE_CIRCLE_H
#define U22_COLLISION_COLLISIONABLE_CIRCLE_H


#include "../Shape/Circle.h"
#include "../Shape/Rectangle.h"
#include "CircleCollisionDetector.h"


namespace u22::collision {
class CollisionableCircle : public u22::shape::Circle {
    using super = u22::shape::Circle;
private:
    //! è’ìÀåüèo
    u22::collision::CircleCollisionDetector _detector;
public:
    using u22::shape::Circle::Circle;

    operator super() {
        return super(x, y, radius);
    }
    operator const super() const {
        return super(x, y, radius);
    }
    CollisionableCircle(const super& circle) {
        x = circle.x;
        y = circle.y;
        radius = circle.radius;
    }
    CollisionableCircle& operator=(const super& circle) {
        x = circle.x;
        y = circle.y;
        radius = circle.radius;
        return *this;
    }

    bool CollisionCircle(const super& target) const {
        return _detector.CollisionCircle(*this, target);
    }
};
}
#endif // !U22_COLLISION_COLLISIONABLE_CIRCLE_H