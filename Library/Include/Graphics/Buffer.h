#ifndef U22_GRAPHICS_BUFFER_H
#define U22_GRAPHICS_BUFFER_H


#include "../Common/Common.h"


namespace u22::graphics {
class Buffer {
private:
    //! ハンドル
    GLuint _id;
    //! タイプ
    GLenum _type;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Buffer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Buffer();
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name="type">種類</param>
    /// <param name="size">サイズ</param>
    /// <param name="data">データ</param>
    /// <param name="usage">使い方</param>
    /// <returns>成功</returns>
    bool Generate(GLenum type, GLsizeiptr size, const void* data, GLenum usage);
    /// <summary>
    /// サブセットを更新
    /// </summary>
    /// <param name="offset">オフセット</param>
    /// <param name="size">サイズ</param>
    /// <param name="data">データ</param>
    void SubsetUpdate(GLintptr offset, GLsizeiptr size, const void* data) const;
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    void Delete(void);
    /// <summary>
    /// 使用
    /// </summary>
    /// <param name=""></param>
    void Bind(void) const;
    /// <summary>
    /// 解除
    /// </summary>
    /// <param name=""></param>
    void UnBind(void) const;
};
}
#endif // !U22_GRAPHICS_BUFFER_H