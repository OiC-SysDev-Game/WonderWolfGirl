#include "Rectangle.h"


u22::shape::Rectangle::Rectangle() :
    left(0.0f),
    top(0.0f),
    right(0.0f),
    bottom(0.0f) {
}

u22::shape::Rectangle::Rectangle(float l, float t, float r, float b) :
    left(l),
    top(t),
    right(r),
    bottom(b) {
}

u22::shape::Rectangle::Rectangle(u22::math::Vector2F  lt, u22::math::Vector2F  rb) :
    u22::shape::Rectangle(lt.x, lt.y, rb.x, rb.y) {
}

u22::shape::Rectangle u22::shape::Rectangle::operator+(const u22::math::Vector2F translate) {
    return u22::shape::Rectangle(
        this->left + translate.x,
        this->top + translate.y,
        this->right + translate.x,
        this->bottom + translate.y);
}

u22::shape::Rectangle& u22::shape::Rectangle::operator+=(const u22::math::Vector2F translate) {
    this->left += translate.x;
    this->top += translate.y;
    this->right += translate.x;
    this->bottom += translate.y;
    return *this;
}

void u22::shape::Rectangle::SetBounds(float pos_x, float pos_y, float width, float height) {
    this->left = pos_x;
    this->top = pos_y;
    this->right = pos_x + width;
    this->bottom = pos_y + height;
}

void u22::shape::Rectangle::SetBounds(const u22::math::Vector2F& pos, const u22::math::Vector2F& size) {
    this->SetBounds(pos.x, pos.y, size.x, size.y);
}

float u22::shape::Rectangle::GetWidth(void) const {
    return this->right - this->left;
}

float u22::shape::Rectangle::GetHeight(void) const {
    return this->bottom - this->top;
}

u22::math::Vector2F u22::shape::Rectangle::GetSize(void) const {
    return u22::math::Vector2F(this->GetWidth(), this->GetHeight());
}

u22::math::Vector2F u22::shape::Rectangle::GetLeftTop(void) const {
    return u22::math::Vector2F(left, top);
}

u22::math::Vector2F u22::shape::Rectangle::GetRightBottom(void) const {
    return u22::math::Vector2F(right, bottom);
}

void u22::shape::Rectangle::Translate(float x, float y) {
    this->left += x;
    this->top += y;
    this->right += x;
    this->bottom += y;
}

void u22::shape::Rectangle::Translate(const u22::math::Vector2F vector) {
    this->Translate(vector.x, vector.y);
}

void u22::shape::Rectangle::Expansion(float value) {
    this->left -= value;
    this->top -= value;
    this->right += value;
    this->bottom += value;
}