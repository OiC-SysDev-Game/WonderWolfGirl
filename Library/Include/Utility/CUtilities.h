#ifndef U22_UTILITY_CUTILITIES_H
#define U22_UTILITY_CUTILITIES_H


namespace u22::utility {
class CUtilities {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CUtilities() = default;
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CUtilities() = default;
    /// <summary>
    /// フレーム当たりの時間
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static float GetFrameSecond(void);
    /// <summary>
    /// FPS
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static float GetFPS(void);
    /// <summary>
    /// ランダム値
    /// </summary>
    /// <param name="min">最小値</param>
    /// <param name="max">最大値</param>
    /// <returns></returns>
    static int GenerateRandom(int min, int max);
    /// <summary>
    /// ランダム値
    /// </summary>
    /// <param name="min">最小値</param>
    /// <param name="max">最大値</param>
    /// <returns></returns>
    static float GenerateRandomF(float min, float max);
};
}
#endif // !U22_UTILITY_CUTILITIES_H