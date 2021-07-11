#include "Buffer.h"


u22::graphics::Buffer::Buffer() :
    _id(),
    _type() {
}

u22::graphics::Buffer::~Buffer() {
}

bool u22::graphics::Buffer::Generate(GLenum type, GLsizeiptr size, const void* data, GLenum usage) {
    _type = type;
    ::glGenBuffers(1, &_id);
    this->Bind();
    ::glBufferData(type, size, data, usage);
    return true;
}

void u22::graphics::Buffer::SubsetUpdate(GLintptr offset, GLsizeiptr size, const void* data) const {
    this->Bind();
    ::glBufferSubData(_type, offset, size, data);
    this->UnBind();
}

void u22::graphics::Buffer::Delete(void) {
    ::glDeleteBuffers(1, &_id);
}

void u22::graphics::Buffer::Bind(void) const {
    ::glBindBuffer(_type, _id);
}

void u22::graphics::Buffer::UnBind(void) const {
    ::glBindBuffer(_type, 0);
}