#ifndef U22_GRAPHICS_FONT_H
#define U22_GRAPHICS_FONT_H


#include <memory>
#include <string>

#include "../Common/Common.h"

#include "FontImage.h"


namespace u22::graphics {
class Font {
private:
    //! パス
    std::string _name;
    //! フォント
    FT_Face _face;
    //! サイズ
    FT_UInt _size;
    //! スロット
    FT_GlyphSlot _slot;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Font();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Font();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetSize(void) const;
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name="path"></param>
    /// <param name=""></param>
    /// <returns></returns>
    bool Generate(const char* path, std::uint32_t size);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="text"></param>
    /// <returns></returns>
    std::shared_ptr<u22::graphics::FontImage> CreateFontImage(FT_ULong text) const;    
};
}
#endif // !U22_GRAPHICS_FONT_H