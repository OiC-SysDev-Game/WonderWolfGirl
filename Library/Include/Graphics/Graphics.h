#ifndef U22_GRAPHICS_GRAPHICS_H
#define U22_GRAPHICS_GRAPHICS_H


#include "../Framework/Window/Window.h"

#include <memory>
#include <unordered_map>

#include "../Math/Vector4.h"
#include "GraphicsDefine.h"
#include "Camera.h"
#include "EffectShader.h"


namespace u22::graphics {
class Graphics {
private:
    //! 初期化
    bool _initialized;
    //! シェーダ
    std::unordered_map<u22::graphics::EffectShaderType, std::shared_ptr<u22::graphics::EffectShader>> _shader_map;
     //! フォント
    FT_Library _font;
    /// <summary>
    /// セットアップ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Setup(void);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool LoadShader(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ReleaseShader(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Graphics();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Graphics();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    FT_Library GetFontPtr(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<u22::graphics::EffectShader> GetEffectShader(u22::graphics::EffectShaderType type) const;
    /// <summary>
    /// クリア
    /// </summary>
    /// <param name="color">色</param>
    /// <param name="depth">深度</param>
    /// <param name="stencil">ステンシル</param>
    void ClearTarget(const u22::math::Vector4F& color, float depth, float stencil);
    /// <summary>
    /// 描画開始
    /// </summary>
    /// <param name=""></param>
    void RenderStart(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="window"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<u22::Window>& window);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_GRAPHICS_H