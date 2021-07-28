#include "Texture.h"

#include "Image.h"


u22::graphics::Texture::Texture() :
    _id(NULL),
    _name(),
    _size() {
}

u22::graphics::Texture::~Texture() {
}

GLuint u22::graphics::Texture::GetID(void) const {
    return this->_id;
}

int u22::graphics::Texture::GetWidth(void) const {
    return this->_size.x;
}

int u22::graphics::Texture::GetHeight(void) const {
    return this->_size.y;
}

u22::math::Vector2I u22::graphics::Texture::GetSize(void) const {
    return this->_size;
}

bool u22::graphics::Texture::Generate(void) {
    ::glGenTextures(1, &_id);
    return true;
}

bool u22::graphics::Texture::TextureMapping(int width, int height) {
    _size.x = width;
    _size.y = height;
    this->Bind();
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    //::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    this->UnBind();
    return true;;
}

bool u22::graphics::Texture::SubImageUpdate(GLint offset_x, GLint offset_y, GLint width, GLint height, const void* pixels) {
    this->Bind();
    //::glTexSubImage2D(GL_TEXTURE_2D, 0, offset_x, offset_y, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, pixels);
    ::glTexSubImage2D(GL_TEXTURE_2D, 0, offset_x, offset_y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    this->UnBind();
    return true;
}

void u22::graphics::Texture::Bind(uint32_t index) const {
    ::glActiveTexture(GL_TEXTURE0 + index);
    ::glBindTexture(GL_TEXTURE_2D, _id);
}

void u22::graphics::Texture::UnBind(void) const {
    ::glBindTexture(GL_TEXTURE_2D, 0);
}

bool u22::graphics::Texture::Load(const char* path) {
    auto image = Image();
    if (!image.Load(path)) {
        return false;
    } // if
    _size.x = image.GetWidth();
    _size.y = image.GetHeight();

    this->Generate();
    this->Bind(0);

    {
        ::glTexImage2D(GL_TEXTURE_2D, 0, image.GetInternalFormat(),
                       _size.x, _size.y, 0, image.GetFormat(),
                       GL_UNSIGNED_BYTE, image.GetPixel());
    }
    {
        // rgba
        ::glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    {
        // Ý’è
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    ::glGenerateMipmap(GL_TEXTURE_2D);
    if (GLEW_EXT_texture_filter_anisotropic) {
        GLfloat largest;
        ::glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
        ::glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
    } // if

    this->UnBind();
    return true;
}

bool u22::graphics::Texture::Release(void) {
    if (_id == NULL) {
        return false;
    } // if
    ::glDeleteTextures(1, &_id);
    _id = NULL;
    return true;
}