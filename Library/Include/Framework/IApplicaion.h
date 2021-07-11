#ifndef U22_FRAMEWORK_IAPPLICAION_H
#define U22_FRAMEWORK_IAPPLICAION_H


namespace u22 {
class IApplicaion {
protected:
    /// <summary>
    /// 設定
    /// </summary>
    /// <param name="name"></param>
    void SetCurrentPath(const char* name = "Resource");
    /// <summary>
    /// 表示
    /// </summary>
    /// <param name=""></param>
    //void PutLocalTime(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    IApplicaion();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    virtual ~IApplicaion();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) = 0;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) = 0;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) = 0;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) = 0;
};
}
#endif // !U22_FRAMEWORK_IAPPLICAION_H