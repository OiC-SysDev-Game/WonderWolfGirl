#ifndef U22_GRAPHICS_TEXTURE_RENDERER_H
#define U22_GRAPHICS_TEXTURE_RENDERER_H


#include <memory>

#include "../Math/Vector2.h"
#include "../Math/Matrix4x4.h"
#include "../Shape/Rectangle.h"
#include "VertexArray.h"
#include "EffectShader.h"
#include "Texture.h"
#include "Camera.h"


namespace u22::graphics {
class TextureRenderer {
private:
    //! 頂点
    u22::graphics::VertexArray _vao;
    //! シェーダ
    std::weak_ptr<u22::graphics::EffectShader> _shader;
    //! テクスチャ
    std::shared_ptr<u22::graphics::Texture> _texture;
    /// <summary>
    /// 転送
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="uniform_rectangle"></param>
    /// <param name="uniform_color"></param>
    /// <param name="model_transform"></param>
    /// <param name="camera"></param>
    void TransferUniform(const std::shared_ptr<u22::graphics::EffectShader>& shader, const u22::shape::Rectangle& uniform_rectangle, const u22::math::Vector4F& uniform_color, const u22::math::Matrix4x4F& model_transform, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    void Draw(void) const;
public:
    /// <summary>    
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetShader(const std::shared_ptr<u22::graphics::EffectShader>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    int GetWidth(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    int GetHeight(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    u22::math::Vector2I GetSize(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool Render(const u22::math::Vector2F& position, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="position">色</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool Render(const u22::math::Vector2F& position, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="rectangle">表示矩形</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool Render(const u22::math::Vector2F& position, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="rectangle">表示矩形</param>
    /// <param name="rectangle">色</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool Render(const u22::math::Vector2F& position, const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="rotate">ラジアン</param>
    /// <param name="camera">カメラ</param>
    /// <param name="axis">軸</param>
    /// <returns></returns>
    bool RenderRotate(const u22::math::Vector2F& position, float rotate, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="rotate">ラジアン</param>
    /// <param name="rectangle">表示矩形</param>
    /// <param name="camera">カメラ</param>
    /// <param name="axis">軸</param>
    /// <returns></returns>
    bool RenderRotate(const u22::math::Vector2F& position, float rotate, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="scale">拡大率</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool RenderScale(const u22::math::Vector2F& position, float scale, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">スクリーン座標</param>
    /// <param name="scale">拡大率</param>
    /// <param name="rectangle">表示矩形</param>
    /// <param name="camera">カメラ</param>
    /// <returns></returns>
    bool RenderScale(const u22::math::Vector2F& position, float scale, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_TEXTURE_RENDERER_H