#ifndef U22_TEST_GAME_APPLICATION_H
#define U22_TEST_GAME_APPLICATION_H


#include "U22.h"

enum tag_SCENENO {								//存在するシーン
    SCENENO_TITLE,
    SCENENO_STAGESELECT,
    SCENENO_GAME,
    SCENENO_END,
};

namespace u22 {
class GameApplication : public u22::IApplicaion {
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameApplication();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameApplication();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !U22_TEST_GAME_APPLICATION_H