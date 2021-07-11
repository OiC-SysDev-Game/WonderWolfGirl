#ifndef U22_GRAPHICS_TEXTURE_H
#define U22_GRAPHICS_TEXTURE_H


#include "../Common/Common.h"

#include <string>

#include "../Math/Vector2.h"


namespace u22::graphics {
class Texture {
private:
    //! ハンドル
    GLuint _id;
    //! 名前
    std::string _name;
    //! サイズ
    u22::math::Vector2I _size;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Texture();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Texture();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    GLuint GetID(void) const;
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
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Generate(void);
    /// <summary>
    /// 設定
    /// </summary>
    /// <param name="width">サイズ</param>
    /// <param name="height">サイズ</param>
    /// <returns></returns>
    bool TextureMapping(int width, int height);
    /// <summary>
    /// 書き換え
    /// </summary>
    /// <param name="offset_x">オフセット</param>
    /// <param name="offset_y">オフセット</param>
    /// <param name="width">サイズ</param>
    /// <param name="height">サイズ</param>
    /// <param name="pixels">データ</param>
    /// <returns></returns>
    bool SubImageUpdate(GLint offset_x, GLint offset_y, GLint width, GLint height, const void* pixels);
    /// <summary>
    /// 使用
    /// </summary>
    /// <param name="index"></param>
    void Bind(uint32_t index = 0) const;
    /// <summary>
    /// 解除
    /// </summary>
    /// <param name=""></param>
    void UnBind(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns>成功</returns>
    bool Load(const char* path);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_GRAPHICS_TEXTURE_H