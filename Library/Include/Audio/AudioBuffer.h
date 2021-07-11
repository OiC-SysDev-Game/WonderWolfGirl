#ifndef U22_AUDIO_AUDIO_BUFFER_H
#define U22_AUDIO_AUDIO_BUFFER_H


#include "../Common/Common.h"

#include "SoundFile.h"


namespace u22::audio {
class AudioBuffer {
private:
    //! ハンドル
    ALuint _id;
    //! スピーカー
    ALuint _source;
    //! ファイル
    u22::audio::SoundFile _file;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AudioBuffer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AudioBuffer();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ALuint GetID(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Generate(void);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    bool Delete(void);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns></returns>
    //bool Load(const char* path);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool Release(void);
    /// <summary>
    /// 再生
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool Play(void) const;
};
}
#endif // !U22_AUDIO_AUDIO_BUFFER_H