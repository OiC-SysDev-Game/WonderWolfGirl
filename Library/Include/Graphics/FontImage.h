#ifndef U22_GRAPHICS_FONT_IMAGE_H
#define U22_GRAPHICS_FONT_IMAGE_H


#include <string>

#include "../Common/Common.h"


namespace u22::graphics {
class FontImage {
public:
    //! オフセット
    int offset_x;
    //! オフセット
    int	offset_y;
    //! サイズ
    int	width;
    //! サイズ
    int	height;
    //! データ
    uint8_t* pixels;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FontImage();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FontImage();
};
}
#endif // !U22_GRAPHICS_FONT_IMAGE_H