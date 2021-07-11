#include "Font.h"

#include "../Framework/Framework.h"


u22::graphics::Font::Font() :
    _name(),
    _face(),
    _size(),
    _slot() {
}

u22::graphics::Font::~Font() {
}

uint32_t u22::graphics::Font::GetSize(void) const {
    return this->_size;
}

bool u22::graphics::Font::Generate(const char* path, std::uint32_t size) {
    if (::FT_New_Face(u22::Framework::GetInfomation()->graphics->GetFontPtr(), path, 0, &_face)) {
        return false;
    } // if
    if (::FT_Set_Pixel_Sizes(_face, size, 0)) {
        return false;
    } // if
    _name = path;
    _size = size;
    _slot = _face->glyph;
    return true;
}

std::shared_ptr<u22::graphics::FontImage> u22::graphics::Font::CreateFontImage(FT_ULong text) const {
    auto image = std::make_shared<u22::graphics::FontImage>();
    FT_Error err = FT_Load_Char(_face, text, FT_LOAD_RENDER);
    if (err) {
        return nullptr;
    } // if
    image->offset_x = _slot->bitmap_left;
    image->offset_y = _size - _slot->bitmap_top;
    image->width = _slot->bitmap.width;
    image->height = _slot->bitmap.rows;
    image->pixels = _slot->bitmap.buffer;

    return image;
}