#ifndef U22_GRAPHICS_FONT_RENDERER_H
#define U22_GRAPHICS_FONT_RENDERER_H


#include <memory>
#include <string>
#include <map>

#include "../Common/Common.h"

#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
#include "../Shape/Rectangle.h"
#include "FontImage.h"
#include "Font.h"
#include "VertexArray.h"
#include "EffectShader.h"
#include "Texture.h"
#include "Camera.h"


namespace u22::graphics {
class FontRenderer {
private:
    //! フォント
    std::shared_ptr<u22::graphics::Font> _font;
    //! 頂点
    u22::graphics::VertexArray _vao;
    //! シェーダ
    std::weak_ptr<u22::graphics::EffectShader> _shader;
    //! テクスチャ
    std::shared_ptr<u22::graphics::Texture> _texture;
    //! テクスチャ
    std::size_t _texture_size;
    //! オフセット
    int _dest_offset_x;
    //! オフセット
    int	_dest_offset_y;
    //! 余白
    int	_margin;
    //! 切り抜きマップ
    std::map<std::string, u22::shape::Rectangle> _slices_map;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    bool IsCodeValid(const char s) const;
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    bool RegisterCharacter(const char* str);
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
    /// コンストラクタ
    /// </summary>
    FontRenderer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FontRenderer();
    /// <summary>    
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetShader(const std::shared_ptr<u22::graphics::EffectShader>& ptr);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <param name="size">サイズ</param>
    /// <returns></returns>
    bool Load(const char* path, uint32_t size = 16);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">ウインドウ座標</param>
    /// <param name="color">色正規化</param>
    /// <param name="text">文字列</param>
    /// <param name="text">カメラ</param>
    /// <returns></returns>
    bool Render(const u22::math::Vector2F& position, const u22::math::Vector4F& color, const std::string& text, const u22::graphics::Camera& camera);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_FONT_RENDERER_H