#ifndef U22_GRAPHICS_VERTEX_ARRAY_H
#define U22_GRAPHICS_VERTEX_ARRAY_H


#include <vector>

#include "../Common/Common.h"

#include "Vertex.h"
#include "Buffer.h"


namespace u22::graphics {
class VertexArray {
private:
    //! ハンドル
    GLuint _id;
    //! トポロジー
    GLenum _topology;
    //! バーテックス
    u22::graphics::Buffer _vertex;
    //! インデックス
    u22::graphics::Buffer _index;
    //! インデックスサイズ
    std::uint32_t _indices_size;

    template <typename Vertex>
    void EnablePosition(int slot) {
        ::glEnableVertexAttribArray(slot);
        ::glVertexAttribPointer(slot, sizeof(Vertex::position) / sizeof(float), GL_FLOAT,
                                GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::position)));
    }
    template <typename Vertex>
    void EnableColor(int slot) {
        ::glEnableVertexAttribArray(slot);
        ::glVertexAttribPointer(slot, sizeof(Vertex::color) / sizeof(float), GL_FLOAT,
                                GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::color)));
    }
    template <typename Vertex>
    void EnableTexcoord(int slot) {
        ::glEnableVertexAttribArray(slot);
        ::glVertexAttribPointer(slot, sizeof(Vertex::texcoord) / sizeof(float), GL_FLOAT,
                                GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord)));
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    VertexArray();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~VertexArray();
    /// <summary>
    /// 生成
    /// </summary>
    /// <typeparam name="Vertex">型</typeparam>
    /// <param name="vertices">バーテックス</param>
    /// <param name="indices">インデックス</param>
    /// <returns>成功</returns>
    template<typename Vertex>
    bool Generate(const std::vector<Vertex>& vertices, const std::vector<std::uint32_t>& indices) {
    }
    template<>
    bool Generate<u22::graphics::ColorVertex>(const std::vector<u22::graphics::ColorVertex>& vertices, const std::vector<std::uint32_t>& indices) {
        using Vertex = u22::graphics::ColorVertex;
        _indices_size = indices.size();

        ::glGenVertexArrays(1, &_id);
        this->Bind();
        if (!_vertex.Generate(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                              vertices.data(), GL_STREAM_DRAW)) {
            return false;
        } // if
        if (!_index.Generate(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indices.size(),
                             indices.data(), GL_STATIC_DRAW)) {
            return false;
        } // if

        int pos = 0; int color = 1;
        this->EnablePosition<Vertex>(pos);
        this->EnableColor<Vertex>(color);

        this->UnBind();
        _vertex.UnBind();
        _index.UnBind();
        return true;
    }
    template<>
    bool Generate<u22::graphics::SpriteVertex>(const std::vector<u22::graphics::SpriteVertex>& vertices, const std::vector<std::uint32_t>& indices) {
        using Vertex = u22::graphics::SpriteVertex;
        _indices_size = indices.size();

        ::glGenVertexArrays(1, &_id);
        this->Bind();
        if (!_vertex.Generate(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                              vertices.data(), GL_STREAM_DRAW)) {
            return false;
        } // if
        if (!_index.Generate(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indices.size(),
                             indices.data(), GL_STATIC_DRAW)) {
            return false;
        } // if

        int pos = 0; int texcoord = 1;
        this->EnablePosition<Vertex>(pos);
        this->EnableTexcoord<Vertex>(texcoord);

        this->UnBind();
        _vertex.UnBind();
        _index.UnBind();
        return true;
    }

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
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    void DrawElements(void) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    void DrawElementsInstanced(uint32_t count) const;
    /// <summary>
    /// トポロジーをLINESにする
    /// </summary>
    /// <param name=""></param>
    void ToLines(void);
    /// <summary>
    /// トポロジーをLINE_STRIPにする
    /// </summary>
    /// <param name=""></param>
    void ToLineStrip(void);
    /// <summary>
    /// トポロジーをTRIANGLESにする
    /// </summary>
    /// <param name=""></param>
    void ToTriangles(void);
    /// <summary>
    /// トポロジーをTRIANGLE_STRIPにする
    /// </summary>
    /// <param name=""></param>
    void ToTriangleStrip(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="offset">オフセット</param>
    /// <param name="size">サイズ</param>
    /// <param name="data">データ</param>
    void UpdateVertexBuffer(GLintptr offset, GLsizeiptr size, const void* data) const;
};
}
#endif // !U22_GRAPHICS_VERTEX_ARRAY_H