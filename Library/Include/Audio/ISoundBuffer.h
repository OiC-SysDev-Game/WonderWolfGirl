#ifndef U22_AUDIO_ISOUND_BUFFER_H
#define U22_AUDIO_ISOUND_BUFFER_H


#include "../Common/Common.h"


namespace u22::audio {
class ISoundBuffer {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ISoundBuffer() = default;
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ISoundBuffer() = default;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="volume"></param>
    virtual void SetVolume(float volume) = 0;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pitch"></param>
    virtual void SetPitch(float pitch) = 0;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="loop"></param>
    virtual void SetLoop(bool loop) = 0;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsPlay(void) const = 0;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsPause(void) const = 0;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsEnd(void) const = 0;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns></returns>
    virtual bool Load(const char* path) = 0;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) = 0;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) = 0;
    /// <summary>
    /// 再生
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Play(void) = 0;
    /// <summary>
    /// 中断
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Pause(void) = 0;
    /// <summary>
    /// 停止
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Stop(void) const = 0;
    /// <summary>
    /// 巻き戻し
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Rewind(void) = 0;
};
}
#endif // !U22_AUDIO_ISOUND_BUFFER_H