#ifndef U22_FRAMEWORK_WINDOW_WINDOW_H
#define U22_FRAMEWORK_WINDOW_WINDOW_H


#include "../../Common/Common.h"

#include <string>


namespace u22 {
class Window {
private:
    //! ウインドウ
    ::GLFWwindow* _handle;
    //! タイトル
    std::string _title;
    //! サイズ
    int _width;
    //! サイズ
    int _height;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Window();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Window();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetHandle(::GLFWwindow* ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ::GLFWwindow* GetHandle(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetWidth(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetHeight(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ShouldClose(void);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="タイトル"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <param name="pos_x"></param>
    /// <param name="pos_y"></param>
    /// <param name="full_screen"></param>
    /// <returns></returns>
    bool Create(const char* title, int width, int height, int pos_x, int pos_y, bool full_screen);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Destroy(void);
    /// <summary>
    /// フリップ
    /// </summary>
    void Present(void) const;
    /// <summary>
    /// イベントポーリング
    /// </summary>
    /// <param name=""></param>
    void PollEvents(void) const;
};
}
#endif // U22_FRAMEWORK_WINDOW_WINDOW_H