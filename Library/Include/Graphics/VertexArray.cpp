#include "VertexArray.h"


u22::graphics::VertexArray::VertexArray() :
    _id(),
    _topology(GL_TRIANGLES),
    _vertex(),
    _index(),
    _indices_size() {
}

u22::graphics::VertexArray::~VertexArray() {
}
/*
bool u22::graphics::VertexArray::Generate(const std::vector<u22::graphics::SpriteVertex>& vertices, const std::vector<std::uint32_t>& indices) {
    _indices_size = indices.size();
    using Vertex = u22::graphics::SpriteVertex;

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
*/

void u22::graphics::VertexArray::Delete(void) {
    ::glDeleteVertexArrays(1, &_id);
    _id = NULL;
}

void u22::graphics::VertexArray::Bind(void) const {
    ::glBindVertexArray(_id);
}

void u22::graphics::VertexArray::UnBind(void) const {
    ::glBindVertexArray(0);
}

void u22::graphics::VertexArray::DrawElements(void) const {
    ::glDrawElements(_topology, _indices_size, GL_UNSIGNED_INT, nullptr);
}

void u22::graphics::VertexArray::DrawElementsInstanced(uint32_t count) const {
    ::glDrawElementsInstanced(_topology, _indices_size, GL_UNSIGNED_INT, nullptr, count);
}

void u22::graphics::VertexArray::ToLines(void) {
    _topology = GL_LINES;
}

void u22::graphics::VertexArray::ToLineStrip(void) {
    _topology = GL_LINE_STRIP;
}

void u22::graphics::VertexArray::ToTriangles(void) {
    _topology = GL_TRIANGLES;
}

void u22::graphics::VertexArray::ToTriangleStrip(void) {
    _topology = GL_TRIANGLE_STRIP;
}

void u22::graphics::VertexArray::UpdateVertexBuffer(GLintptr offset, GLsizeiptr size, const void* data) const {
    this->_vertex.SubsetUpdate(offset, size, data);
}