#ifndef U22_SHAPE_CIRCLE_H
#define U22_SHAPE_CIRCLE_H


#include "../Math/Vector2.h"


namespace u22::shape {
class Circle {
public:
    union {
        struct {
            //! 位置
            float x;
            //! 位置
            float y;
        };
        struct {
            //! 位置
            u22::math::Vector2F position;
        };
    };
    //! 半径
    float radius;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Circle();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="x">x</param>
    /// <param name="y">y</param>
    /// <param name="r">半径</param>
    Circle(float x, float y, float r);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">位置</param>
    /// <param name="r">半径</param>
    Circle(u22::math::Vector2F pos, float r);
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="translate"></param>
    /// <returns></returns>
    u22::shape::Circle operator+(const u22::math::Vector2F translate) const;
    /// <summary>
    /// 遷移
    /// </summary>
    /// <param name="translate"></param>
    /// <returns></returns>
    u22::shape::Circle& operator+=(const u22::math::Vector2F translate);
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
};
}
#endif // !U22_SHAPE_CIRCLE_H