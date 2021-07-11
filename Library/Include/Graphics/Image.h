#ifndef U22_FRAMEWORK_IMAGE_H
#define U22_FRAMEWORK_IMAGE_H


#include "../Common/Common.h"


namespace u22::graphics {
class Image {
private:
    //! データ
    unsigned char* _pixels;
    //! サイズ
    int _width;
    //! サイズ
    int _height;
    //! フォーマット
    int _internal_format;
    //! フォーマット
    int _format;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Image();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Image();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>データ</returns>
    unsigned char* GetPixel(void) const;
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
    /// <returns>フォーマット</returns>
    int GetInternalFormat(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>フォーマット</returns>
    int GetFormat(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
};
}
#endif // !U22_FRAMEWORK_IMAGE_H