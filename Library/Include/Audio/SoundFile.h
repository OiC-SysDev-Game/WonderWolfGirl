#ifndef U22_AUDIO_SOUND_FILE_H
#define U22_AUDIO_SOUND_FILE_H


#include <vector>

#include "../Common/Common.h"


namespace u22::audio {
class SoundFile {
private:
    //! データ
    SNDFILE* _file;
    //! 情報
    SF_INFO _info;
    //! データ
    std::vector<int> _data;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundFile();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SoundFile();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ALenum GetFormat(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const void* GetData(void) const;
    /// <summary>::
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ALsizei GetSize(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ALsizei GetFrequency(void) const;
    /// <summary>
    /// 開く
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Open(const char* path);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="offset"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    int Read(int offset, int size);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !U22_AUDIO_SOUND_FILE_H