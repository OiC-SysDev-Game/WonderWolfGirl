#ifndef U22_GRAPHICS_EFFECT_SHADER_H
#define U22_GRAPHICS_EFFECT_SHADER_H


#include "../Common/Common.h"

#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4x4.h"


namespace u22::graphics {
class EffectShader {
private:
    GLuint _vertex_id;
    GLuint _fragment_id;
    //! シェーダハンドル
    GLuint _id;
    //! ユニフォームハンドル
    GLuint _uniform_handle;

    /// <summary>
    /// コンパイル
    /// </summary>
    /// <param name="path"></param>
    /// <param name="out"></param>
    /// <returns></returns>
    bool Compile(const char* path, GLuint& out);
    bool Check(const GLuint id, const GLenum type);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectShader();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectShader();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    GLuint GetID(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="vert_path">パス</param>
    /// <param name="frag_path">パス</param>
    /// <returns>成功</returns>
    bool Load(const char* vert_path, const char* frag_path);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// 転送
    /// </summary>
    /// <param name="name"></param>
    /// <param name="value"></param>
    void TransferUniform(const char* name, const float& value);
    /// <summary>
    /// 転送
    /// </summary>
    /// <param name="name"></param>
    /// <param name="vector2"></param>
    void TransferUniform(const char* name, const u22::math::Vector2F& vector2);
    /// <summary>
    /// 転送
    /// </summary>
    /// <param name="name"></param>
    /// <param name="vector4"></param>
    void TransferUniform(const char* name, const u22::math::Vector4F& vector4);
    /// <summary>
    /// 転送
    /// </summary>
    /// <param name="name"></param>
    /// <param name="matrix"></param>
    /// <param name="transpose"></param>
    void TransferUniform(const char* name, const glm::mat4& matrix, bool transpose = false);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name=""></param>
    void Attach(void);
    /// <summary>
    /// リンク
    /// </summary>
    /// <param name=""></param>
    void Link(void);
    //bool GenerateUniformBuffer(const char* name, std::size_t size, void* data);
    //bool BindUniformBuffer(const char* name, std::size_t size, void* data);
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    void Enable(void);
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    void Disable(void);
};
}
#endif // !U22_GRAPHICS_EFFECT_SHADER_H