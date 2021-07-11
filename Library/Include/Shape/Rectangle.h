#ifndef U22_SHAPE_RECTANGLE_H
#define U22_SHAPE_RECTANGLE_H


#include "../Math/Vector2.h"


namespace u22::shape {
class Rectangle {
public:
    //! 左
    float left;
    //! 上
    float top;
    //! 右
    float right;
    //! 下
    float bottom;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Rectangle();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="l">左</param>
    /// <param name="t">上</param>
    /// <param name="r">右</param>
    /// <param name="b">下</param>
    Rectangle(float l, float t, float r, float b);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="lt">左上</param>
    /// <param name="rb">右下</param>
    Rectangle(u22::math::Vector2F lt, u22::math::Vector2F rb);
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="translate"></param>
    /// <returns></returns>
    Rectangle operator+(const u22::math::Vector2F translate);    
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="translate"></param>
    /// <returns></returns>
    Rectangle& operator+=(const u22::math::Vector2F translate);    
    /// <summary>
    /// 設定
    /// </summary>
    /// <param name="pos_x">位置</param>
    /// <param name="pos_y">位置</param>
    /// <param name="width">サイズ</param>
    /// <param name="height">サイズ</param>
    void SetBounds(float pos_x, float pos_y, float width, float height);
    /// <summary>
    /// 設定
    /// </summary>
    /// <param name="pos">位置</param>
    /// <param name="size">サイズ</param>
    void SetBounds(const u22::math::Vector2F& pos, const u22::math::Vector2F& size);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    float GetWidth(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    float GetHeight(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    u22::math::Vector2F GetSize(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>左上</returns>
    u22::math::Vector2F GetLeftTop(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>右下</returns>
    u22::math::Vector2F GetRightBottom(void) const;
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void Translate(float x, float y);    
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="vector"></param>
    void Translate(const u22::math::Vector2F vector);    
    /// <summary>
    /// 拡張
    /// </summary>
    /// <param name="value"></param>
    void Expansion(float value);
};
}
#endif // !U22_SHAPE_RECTANGLE_H