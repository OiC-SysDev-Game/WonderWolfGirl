#include "TextureRenderer.h"

#include "../Common/Common.h"
#include "../Framework/Framework.h"
#include "../Math/MathDefine.h"


void u22::graphics::TextureRenderer::TransferUniform(
    const std::shared_ptr<u22::graphics::EffectShader>& shader, const u22::shape::Rectangle& uniform_rectangle, const u22::math::Vector4F& uniform_color,
    const u22::math::Matrix4x4F& model_transform, const u22::graphics::Camera& camera) const {
    shader->TransferUniform("uniform_size", _texture->GetSize());
    shader->TransferUniform("uniform_rectangle", *reinterpret_cast<const u22::math::Vector4F*>(&uniform_rectangle));
    shader->TransferUniform("uniform_color", uniform_color);
    shader->TransferUniform("view_projection", camera.GetViewProjectionMatrix());
    shader->TransferUniform("model_transform", model_transform);
}

void u22::graphics::TextureRenderer::Draw(void) const {
    _vao.Bind();
    _texture->Bind();
    _vao.DrawElements();
    _vao.UnBind();
    _texture->UnBind();
}

void u22::graphics::TextureRenderer::SetShader(const std::shared_ptr<u22::graphics::EffectShader>& ptr) {
    this->_shader = ptr;
}

int u22::graphics::TextureRenderer::GetWidth(void) const {
    return this->_texture->GetWidth();
}

int u22::graphics::TextureRenderer::GetHeight(void) const {
    return this->_texture->GetHeight();
}

u22::math::Vector2I u22::graphics::TextureRenderer::GetSize(void) const {
    return this->_texture->GetSize();
}

bool u22::graphics::TextureRenderer::Load(const char* path) {
    _texture = std::make_shared<u22::graphics::Texture>();
    if (!_texture->Load(path)) {
        _texture->Release();
        _texture.reset();
        return false;
    } // if
    if (!_vao.Generate<u22::graphics::SpriteVertex>(u22::graphics::kSpriteVertices, u22::graphics::kSpriteIndices)) {
        _vao.Delete();
        return false;
    } // if

    auto shader = u22::Framework::GetInfomation()->graphics->GetEffectShader(u22::graphics::EffectShaderType::Sprite);
    if (!shader) {
        return false;
    } // if
    this->SetShader(shader);
    return true;
}

bool u22::graphics::TextureRenderer::Render(const u22::math::Vector2F& position, const u22::graphics::Camera& camera) const {
    auto rect = u22::shape::Rectangle(0.0f, 0.0f, static_cast<float>(_texture->GetSize().x), static_cast<float>(_texture->GetSize().y));
    return this->Render(position, rect, u22::math::vec4::kOne, camera);
}

bool u22::graphics::TextureRenderer::Render(const u22::math::Vector2F& position, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    auto rect = u22::shape::Rectangle(0.0f, 0.0f, static_cast<float>(_texture->GetSize().x), static_cast<float>(_texture->GetSize().y));
    return this->Render(position, rect, color, camera);
}

bool u22::graphics::TextureRenderer::Render(const u22::math::Vector2F& position, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const {
    return this->Render(position, rectangle, u22::math::vec4::kOne, camera);
}

bool u22::graphics::TextureRenderer::Render(const u22::math::Vector2F& position, const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    auto pos = position;
    auto scale = u22::math::Vector3F(rectangle.GetSize(), 1.0f);

    // offset
    pos.x += scale.x * 0.5f;
    pos.y += scale.y * 0.5f;
    // flip
    pos.y *= -1.0f;

    shader->Enable();
    this->TransferUniform(shader, rectangle, color, u22::math::utility::ConputeTransform(pos, u22::math::Vector3F(), scale), camera);
    this->Draw();
    shader->Disable();
    return true;
}

bool u22::graphics::TextureRenderer::RenderRotate(const u22::math::Vector2F& position, float rotate, const u22::graphics::Camera& camera) const {
    auto rect = u22::shape::Rectangle(0.0f, 0.0f, static_cast<float>(_texture->GetSize().x), static_cast<float>(_texture->GetSize().y));
    return this->RenderRotate(position, rotate, rect, camera);
}

bool u22::graphics::TextureRenderer::RenderRotate(const u22::math::Vector2F& position, float rotate, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    auto pos = position;
    auto scale = u22::math::Vector3F(rectangle.GetSize(), 1.0f);

    // offset
    pos.x += scale.x * 0.5f;
    pos.y += scale.y * 0.5f;
    // flip
    pos.y *= -1.0f;

    shader->Enable();
    this->TransferUniform(shader, rectangle, u22::math::vec4::kOne, u22::math::utility::ConputeTransform(pos, u22::math::Vector3F(0.0f, 0.0f, rotate), scale), camera);
    this->Draw();
    shader->Disable();
    return true;
}

bool u22::graphics::TextureRenderer::RenderScale(const u22::math::Vector2F& position, float scale, const u22::graphics::Camera& camera) const {
    auto rect = u22::shape::Rectangle(0.0f, 0.0f, static_cast<float>(_texture->GetSize().x), static_cast<float>(_texture->GetSize().y));
    return this->RenderScale(position, scale, rect, camera);
}

bool u22::graphics::TextureRenderer::RenderScale(const u22::math::Vector2F& position, float scale, const u22::shape::Rectangle& rectangle, const u22::graphics::Camera& camera) const {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    auto pos = position;
    auto sca = u22::math::Vector3F(rectangle.GetSize(), 1.0f) * scale;

    // offset
    pos.x += sca.x * 0.5f;
    pos.y += sca.y * 0.5f;
    // flip
    pos.y *= -1.0f;

    shader->Enable();
    this->TransferUniform(shader, rectangle, u22::math::vec4::kOne, u22::math::utility::ConputeTransform(pos, u22::math::Vector3F(), sca), camera);
    this->Draw();
    shader->Disable();
    return true;
}

bool u22::graphics::TextureRenderer::Release(void) {
    _texture->Release();
    _vao.Delete();
    return true;
}