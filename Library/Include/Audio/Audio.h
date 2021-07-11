#ifndef U22_AUDIO_AUDIO_H
#define U22_AUDIO_AUDIO_H


#include "../Common/Common.h"


namespace u22::audio {
class Audio {
private:
    //! デバイス
    ALCdevice* _device;
    //! コンテキスト
    ALCcontext* _context;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Audio();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Audio();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_AUDIO_AUDIO_H