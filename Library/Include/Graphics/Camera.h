#ifndef U22_GRAPHICS_CAMERA_H
#define U22_GRAPHICS_CAMERA_H


#include "../Common/Common.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/MathDefine.h"


namespace u22::graphics {
class Camera {
private:
    //! ラジアン
    float _fovy;
    //! 比
    float _aspect;
    //! 閾値
    float _near;
    //! 閾値
    float _far;
    //! 位置
    u22::math::Vector3F _position;
    //! 対象
    u22::math::Vector3F _target;
    //! 向き
    u22::math::Vector3F _up;
    //! ビュー
    glm::mat4 _view_matrix;
    //! 射影
    glm::mat4 _projection_matrix;
    //! ビュー射影
    glm::mat4 _view_projection;
    
    //! ビュー射影
    u22::math::Matrix4x4F _mock;
    
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateOrtho(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdatePerspective(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Camera();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Camera();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(u22::math::Vector3F pos);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    u22::math::Vector3F  GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>ビュー</returns>
    glm::mat4 GetViewMatrix(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>プロジェクション</returns>
    glm::mat4 GetProjectionMatrix(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>ビュープロジェクション</returns>
    glm::mat4 GetViewProjectionMatrix(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initalize2DCamera(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void Update(void);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    void Create2D(int width, int height);
};
}
#endif // !U22_GRAPHICS_CAMERA_H