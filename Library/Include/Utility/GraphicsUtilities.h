#ifndef U22_UTILITY_GRAPHICS_UTILITIES_H
#define U22_UTILITY_GRAPHICS_UTILITIES_H


#include "../Graphics/FontRenderer.h"
#include "../Graphics/CircleRenderer.h"
#include "../Graphics/RectangleRenderer.h"


namespace u22::utility {
class GraphicsUtilities {
private:
    //! 文字
    static u22::graphics::FontRenderer _font;
    //! 円
    static u22::graphics::CircleRenderer _circle;
    //! 矩形
    static u22::graphics::RectangleRenderer _rectangle;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GraphicsUtilities() = default;
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GraphicsUtilities() = default;
    /// <summary>
    /// セットアップ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static bool Setup(void);
    /// <summary>
    /// クリーンナップ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static bool Cleanup(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position"></param>
    /// <param name="color"></param>
    /// <param name="text"></param>
    /// <param name="camera"></param>
    /// <returns></returns>
    static bool RenderString(const u22::math::Vector2F& position, const u22::math::Vector4F& color, const std::string& text, const u22::graphics::Camera& camera);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <returns></returns>
    static bool RenderLineCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <returns></returns>
    static bool RenderLineRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <returns></returns>
    static bool RenderFillCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <returns></returns>
    static bool RenderFillRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera);
};
}
#endif // !U22_UTILITY_GRAPHICS_UTILITIES_H