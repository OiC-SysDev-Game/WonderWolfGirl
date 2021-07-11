#ifndef U22_AUDIO_SOUND_BUFFER_H
#define U22_AUDIO_SOUND_BUFFER_H


#include "ISoundBuffer.h"

#include "../Common/Common.h"

#include "SoundFile.h"
#include "AudioBuffer.h"


namespace u22::audio {
class SoundBuffer : public u22::audio::ISoundBuffer {
private:
    //! ハンドル
    ALuint _id;
    //! スピーカー
    ALuint _source;
    //! ファイル
    u22::audio::SoundFile _file;
    //! ループ
    bool _loop;
    //! 終了フラグ
    bool _end;
    /// <summary>
    /// 巻き戻し
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Rewind(void) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pitch"></param>
    virtual void SetPitch(float pitch) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundBuffer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SoundBuffer();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="volume"></param>
    virtual void SetVolume(float volume) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="loop"></param>
    virtual void SetLoop(bool loop) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsPlay(void) const override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsPause(void) const override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsEnd(void) const override;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns></returns>
    virtual bool Load(const char* path) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 再生
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Play(void) override;
    /// <summary>
    /// 中断
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Pause(void) override;
    /// <summary>
    /// 停止
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Stop(void) const override;
};
}
#endif // !U22_AUDIO_SOUND_BUFFER_H