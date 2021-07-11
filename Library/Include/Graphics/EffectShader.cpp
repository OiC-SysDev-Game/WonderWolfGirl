#include "EffectShader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


bool u22::graphics::EffectShader::Compile(const char* path, GLuint& out) {
    std::ifstream stream(path, std::ios::in);
    if (!stream.is_open()) {
        return false;
    } // if
    std::stringstream buffer;
    buffer << stream.rdbuf();
    auto code = buffer.str();
    stream.close();

    const char* source = code.c_str();
    ::glShaderSource(out, 1, &source, NULL);
    ::glCompileShader(out);
    return true;
}
bool u22::graphics::EffectShader::Check(const GLuint id, const GLenum type) {
    int info_log_length;
    ::glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::string message;
        message.resize(info_log_length + 1);
        ::glGetShaderInfoLog(id, info_log_length,
                             NULL, message.data());
        std::cout << message.data();
        return false;
    } // if
    return true;
}
u22::graphics::EffectShader::EffectShader() :
    _vertex_id(),
    _fragment_id(),
    _id(),
    _uniform_handle() {
}

u22::graphics::EffectShader::~EffectShader() {
}

GLuint u22::graphics::EffectShader::GetID(void) const {
    return this->_id;
}

bool u22::graphics::EffectShader::Load(const char* vert_path, const char* frag_path) {
    // vert
    _vertex_id = ::glCreateShader(GL_VERTEX_SHADER);
    if (!this->Compile(vert_path, _vertex_id)) {
        return false;
    } // if
    if (!this->Check(_vertex_id, GL_COMPILE_STATUS)) {
        return false;
    } // if
    // frag
    _fragment_id = ::glCreateShader(GL_FRAGMENT_SHADER);
    if (!this->Compile(frag_path, _fragment_id)) {
        return false;
    } // if
    if (!this->Check(_fragment_id, GL_COMPILE_STATUS)) {
        return false;
    } // if


    // çÏê¨
    _id = ::glCreateProgram();
    if (_id == NULL) {
        return false;
    } // if

    ::glAttachShader(_id, _vertex_id);
    ::glAttachShader(_id, _fragment_id);
    ::glLinkProgram(_id);
    // ï–ïtÇØ
    ::glDetachShader(_id, _vertex_id);
    ::glDetachShader(_id, _fragment_id);
    ::glDeleteShader(_vertex_id);
    ::glDeleteShader(_fragment_id);
    _vertex_id = NULL;
    _fragment_id = NULL;
    return true;
}

bool u22::graphics::EffectShader::Release(void) {
    ::glDeleteProgram(_id);
    return true;
}

void u22::graphics::EffectShader::TransferUniform(const char* name, const float& value) {
    auto location = ::glGetUniformLocation(_id, name);
    ::glUniform1f(location, value);
}

void u22::graphics::EffectShader::TransferUniform(const char* name, const u22::math::Vector2F& vector2) {
    auto location = ::glGetUniformLocation(_id, name);
    ::glUniform2fv(location, 1, reinterpret_cast<const float*>(&vector2));
}

void u22::graphics::EffectShader::TransferUniform(const char* name, const u22::math::Vector4F& vector4) {
    auto location = ::glGetUniformLocation(_id, name);
    ::glUniform4fv(location, 1, reinterpret_cast<const float*>(&vector4));
}

void u22::graphics::EffectShader::TransferUniform(const char* name, const glm::mat4& matrix, bool transpose) {
    auto location = ::glGetUniformLocation(_id, name);
    ::glUniformMatrix4fv(location, 1, transpose, reinterpret_cast<const float*>(&matrix));
}

void u22::graphics::EffectShader::Attach(void) {
}

void u22::graphics::EffectShader::Link(void) {
}

void u22::graphics::EffectShader::Enable(void) {
    ::glUseProgram(_id);
}

void u22::graphics::EffectShader::Disable(void) {
    ::glUseProgram(0);
}