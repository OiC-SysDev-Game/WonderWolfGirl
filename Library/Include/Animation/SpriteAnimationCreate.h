#ifndef U22_ANIMATION_SPRITE_ANIMATION_CREATE_H
#define U22_ANIMATION_SPRITE_ANIMATION_CREATE_H


#include <vector>
#include <string>


namespace u22::animation {
struct SpriteAnimationCreatePattern {
    //! フレームウェイト
    float wait = 0.0f;
    //! パターン番号
    int no = 0;
    //! パターン段
    int step = 0;
};

class SpriteAnimationCreate {
private:
public:
    //!<アニメーション名
    std::string name;
    //! Xオフセット位置
    float offset_x;
    //! Yオフセット位置
    float offset_y;
    //! 幅
    float width;
    //! 高さ
    float height;
    //! ループフラグ
    bool loop;
    //!<パターン
    std::vector<SpriteAnimationCreatePattern> pattern;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    //SpriteAnimationCreate();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="str"></param>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="w"></param>
    /// <param name="h"></param>
    /// <param name="l"></param>
    /// <param name="p"></param>
    //SpriteAnimationCreate(const char* str, float x, float y, float w, float h, bool l, std::vector<SpriteAnimationCreatePattern>& p);
    /// <summary>
    /// デストラクタ
    /// </summary>
    //~SpriteAnimationCreate();
};
}
#endif // !U22_ANIMATION_SPRITE_ANIMATION_CREATE_H