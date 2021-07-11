#include "CircleCollisionDetector.h"


u22::collision::CircleCollisionDetector::CircleCollisionDetector() {
}

u22::collision::CircleCollisionDetector::~CircleCollisionDetector() {
}

bool u22::collision::CircleCollisionDetector::CollisionCircle(const u22::shape::Circle& a, const u22::shape::Circle& b) const {
    return
        std::powf(a.position.x - b.position.x, 2.0f) +
        std::powf(a.position.y - b.position.y, 2.0f) <=
        std::powf(a.radius + b.radius, 2.0f);
}