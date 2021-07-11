#ifndef U22_GRAPHICS_CIRCLE_RENDERER_H
#define U22_GRAPHICS_CIRCLE_RENDERER_H


#include <memory>

#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
#include "../Shape/Circle.h"
#include "VertexArray.h"
#include "EffectShader.h"
#include "Camera.h"


namespace u22::graphics {
class CircleRenderer {
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
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <param name="camera"></param>
    /// <param name="vao"></param>
    /// <returns></returns>
    bool RenderCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color,
                         const u22::graphics::Camera& camera, const u22::graphics::VertexArray& vao) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CircleRenderer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CircleRenderer();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    //bool Render(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool RenderLineCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="circle"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool RenderFillCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_CIRCLE_RENDERER_H