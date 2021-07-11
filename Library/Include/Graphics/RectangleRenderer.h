#ifndef U22_GRAPHICS_RECTANGLE_RENDERER_H
#define U22_GRAPHICS_RECTANGLE_RENDERER_H


#include <memory>

#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
#include "../Shape/Rectangle.h"
#include "VertexArray.h"
#include "EffectShader.h"
#include "Camera.h"


namespace u22::graphics {
class RectangleRenderer {
private:
    //! 頂点
    u22::graphics::VertexArray _line_vao;
    //! 頂点
    u22::graphics::VertexArray _fill_vao;
    //! シェーダ
    std::weak_ptr<u22::graphics::EffectShader> _shader;
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GenerateLineVAO(void);
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GenerateFillVAO(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <param name="vao"></param>
    /// <returns></returns>
    bool RenderRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, 
                         const u22::graphics::Camera& camera, const u22::graphics::VertexArray& vao) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RectangleRenderer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~RectangleRenderer();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool RenderLineRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool RenderFillRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_RECTANGLE_RENDERER_H