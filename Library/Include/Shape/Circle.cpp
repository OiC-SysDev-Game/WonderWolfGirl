#include "Circle.h"


u22::shape::Circle::Circle() :
    position(),
    radius(0.0f) {
}

u22::shape::Circle::Circle(float x, float y, float r) :
    position(x, y),
    radius(r) {
}

u22::shape::Circle::Circle(u22::math::Vector2F pos, float r) :
    u22::shape::Circle(pos.x, pos.y, r) {
}

u22::shape::Circle u22::shape::Circle::operator+(const u22::math::Vector2F translate) const {
    return u22::shape::Circle(radius, position.x + translate.x, position.x + translate.y);
}

u22::shape::Circle& u22::shape::Circle::operator+=(const u22::math::Vector2F translate) {
    //this->position += translate;
    this->position.x += translate.x;
    this->position.y += translate.y;
    return *this;
}

void u22::shape::Circle::Translate(float x, float y) {
    this->position.x += x;
    this->position.y += y;
}

void u22::shape::Circle::Translate(const u22::math::Vector2F vector) {
    this->Translate(vector.x, vector.y);
}