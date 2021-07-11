#include "Image.h"

#include "../External/stb/stb_image.h"


u22::graphics::Image::Image() :
    _pixels(),
    _width(),
    _height(),
    _internal_format(GL_RGBA),
    _format(GL_RGBA) {
}

u22::graphics::Image::~Image() {
    ::stbi_image_free(_pixels);
}

unsigned char* u22::graphics::Image::GetPixel(void) const {
    return this->_pixels;
}

int u22::graphics::Image::GetWidth(void) const {
    return this->_width;
}

int u22::graphics::Image::GetHeight(void) const {
    return this->_height;
}

int u22::graphics::Image::GetInternalFormat(void) const {
    return this->_internal_format;
}

int u22::graphics::Image::GetFormat(void) const {
    return this->_format;
}

bool u22::graphics::Image::Load(const char* path) {
    _pixels = ::stbi_load(path, &_width, &_height, nullptr, STBI_rgb_alpha);
    if (!_pixels) {
        return false;
    } // if
    return true;
}