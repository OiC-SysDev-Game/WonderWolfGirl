#include "GraphicsUtilities.h"


u22::graphics::FontRenderer u22::utility::GraphicsUtilities::_font;
u22::graphics::CircleRenderer u22::utility::GraphicsUtilities::_circle;
u22::graphics::RectangleRenderer u22::utility::GraphicsUtilities::_rectangle;


bool u22::utility::GraphicsUtilities::Setup(void) {
    if (!_font.Load("../Resource/font/RictyDiminishedDiscord-Regular.ttf", 32)) {
        if (!_font.Load("Resource/font/RictyDiminishedDiscord-Regular.ttf", 32)) {
            return false;
        } // 
    } // if


    if (!_rectangle.Initialize()) {
        return false;
    } // if
    if (!_circle.Initialize()) {
        return false;
    } // if
    return true;
}

bool u22::utility::GraphicsUtilities::Cleanup(void) {
    _font.Release();
    _circle.Release();
    _rectangle.Release();
    return true;
}

bool u22::utility::GraphicsUtilities::RenderString(const u22::math::Vector2F& position, const u22::math::Vector4F& color, const std::string& text, const u22::graphics::Camera& camera) {
    return _font.Render(position, color, text, camera);
}

bool u22::utility::GraphicsUtilities::RenderLineCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) {
    return _circle.RenderLineCircle(circle, color, camera);
}

bool u22::utility::GraphicsUtilities::RenderFillCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) {
    return _circle.RenderFillCircle(circle, color, camera);
}

bool u22::utility::GraphicsUtilities::RenderLineRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) {
    return _rectangle.RenderLineRectangle(rectangle, color, camera);
}

bool u22::utility::GraphicsUtilities::RenderFillRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) {
    return _rectangle.RenderFillRectangle(rectangle, color, camera);
}