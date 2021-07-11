#ifndef U22_FRAMEWORK_FRAMEWORK_H
#define U22_FRAMEWORK_FRAMEWORK_H


#include <memory>

#include "../Common/Common.h"

#include "../Clock/Clock.h"
#include "Window/Window.h"
#include "../Input/Input.h"
#include "../Graphics/Graphics.h"
#include "../Audio/Audio.h"
#include "IApplicaion.h"


namespace u22 {
struct ApplicationInfo {
    //! 位置
    int window_position_x ;
    //! 位置
    int window_position_y ;
    //! サイズ
    int window_width ;
    //! サイズ
    int window_height;
    //! フルスクリーン
    bool full_screen_mode;
};
struct FrameworkInfo {
public:
    //! クロック
    std::shared_ptr<u22::clock::Clock> clock;
    //! ウインドウ
    std::shared_ptr<u22::Window> window;
    //! インプット
    std::shared_ptr<u22::input::Input> input;
    //! グラフィックス
    std::shared_ptr<u22::graphics::Graphics> graphics;
    //! オーディオ
    std::shared_ptr<u22::audio::Audio> audio;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FrameworkInfo() = default;
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FrameworkInfo() = default;

    std::shared_ptr<u22::Window> GetWindow(void) const {
        return this->window;
    }
};
class Framework {
private:
    //! 構成情報
    static u22::FrameworkInfo _infomation;
    //! クロック
    std::shared_ptr<u22::clock::Clock> _clock;
    //! ウインドウ
    std::shared_ptr<u22::Window> _window;
    //! インプット
    std::shared_ptr<u22::input::Input> _input;
    //! グラフィックス
    std::shared_ptr<u22::graphics::Graphics> _graphics;
    //! オーディオ
    std::shared_ptr<u22::audio::Audio> _audio;
    //! アプリケーション
    std::shared_ptr<u22::IApplicaion> _applicaion;
public:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static u22::FrameworkInfo* GetInfomation(void);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Framework();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Framework();
    /// <summary>
    /// セットアップ
    /// </summary>
    /// <param name="ptr"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool Setup(const std::shared_ptr<u22::IApplicaion>& ptr, u22::ApplicationInfo* info);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name=""></param>
    /// <returns>結果</returns>
    int Run(void);
    /// <summary>
    /// クリーンナップ
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    bool Cleanup(void);
};
}
#endif // !U22_FRAMEWORK_FRAMEWORK_H