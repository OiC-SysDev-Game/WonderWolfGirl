#include "RectangleCollisionDetector.h"


u22::collision::RectangleCollisionDetector::RectangleCollisionDetector() {
}

u22::collision::RectangleCollisionDetector::~RectangleCollisionDetector() {
}

bool u22::collision::RectangleCollisionDetector::CollisionRectangle(const u22::shape::Rectangle& a, const u22::shape::Rectangle& b) const {
    return(a.left < b.right) && (b.left < a.right) && (a.top < b.bottom) && (b.top < a.bottom);
}

bool u22::collision::RectangleCollisionDetector::CollisionCircle(const u22::shape::Rectangle& rect, const u22::shape::Circle& circle) const {
    float d;
    if (rect.left <= circle.x && circle.x <= rect.right &&
        rect.top <= circle.y && circle.y <= rect.bottom) {
        return true;
    } // if

    if (std::abs(circle.x - rect.left) <= circle.radius) {
        d = std::sqrtf(circle.radius * circle.radius - ((circle.x - rect.left) * (circle.x - rect.left)));
        if ((rect.top <= circle.y + d && circle.y + d <= rect.bottom) || (rect.top <= circle.y - d && circle.y - d <= rect.bottom)) {
            return true;
        } // if
    } // if
    if (std::abs(circle.x - rect.right) <= circle.radius) {
        d = std::sqrtf(circle.radius * circle.radius - ((circle.x - rect.right) * (circle.x - rect.right)));
        if ((rect.top <= circle.y + d && circle.y + d <= rect.bottom) || (rect.top <= circle.y - d && circle.y - d <= rect.bottom)) {
            return true;
        } // if
    } // if
    if (std::abs(circle.y - rect.top) <= circle.radius) {
        d = std::sqrtf(circle.radius * circle.radius - ((circle.y - rect.top) * (circle.y - rect.top)));
        if ((rect.left <= circle.x + d && circle.x + d <= rect.right) || (rect.left <= circle.x - d && circle.x - d <= rect.right)) {
            return true;
        } // if
    } // if
    if (std::abs(circle.y - rect.bottom) <= circle.radius) {
        d = std::sqrtf(circle.radius * circle.radius - ((circle.y - rect.bottom) * (circle.y - rect.bottom)));
        if ((rect.left <= circle.x + d && circle.x + d <= rect.right) || (rect.left <= circle.x - d && circle.x - d <= rect.right)) {
            return true;
        } // if
    } // if
    return false;
}