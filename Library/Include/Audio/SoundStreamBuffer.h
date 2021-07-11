#ifndef U22_AUDIO_SOUND_STREAM_BUFFER_H
#define U22_AUDIO_SOUND_STREAM_BUFFER_H


#include <array>
#include <vector>

#include "ISoundBuffer.h"

#include "../Common/Common.h"

#include "AudioBuffer.h"
#include "SoundFile.h"


namespace u22::audio {
class SoundStreamBuffer : public u22::audio::ISoundBuffer {
private:
    //! ボイス
    ALuint _source;
    //! バッファ
    std::array<ALuint,2> _buffers;
    //! データ
    SNDFILE* _file;
    //! 情報
    SF_INFO _info;
    //! データ
    std::vector<int> _stream_buffers[2];
    //! 再生位置
    sf_count_t _position;
    //! 現在
    int _current;
    //! 次
    int _next;
    //! 終了
    bool _eof;
    //! 終了フラグ
    bool _end;
    //! フォーマット
    ALenum _format;
    //! サイズ
    ALuint _buffer_size;
    //! int shortの比
    std::uint32_t _byte_size_coefficient;
    //! ループ
    bool _loop;

    /// <summary>
    /// ループ処理
    /// </summary>
    /// <param name=""></param>
    void Loop(void);
    /// <summary>
    /// 書き込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ALuint WhiteNextData(ALuint buffer);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pitch"></param>
    virtual void SetPitch(float pitch) override;
    /// <summary>
    /// 巻き戻し
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Rewind(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundStreamBuffer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SoundStreamBuffer();
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
#endif // !U22_AUDIO_SOUND_STREAM_BUFFER_H