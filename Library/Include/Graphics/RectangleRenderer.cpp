#include "RectangleRenderer.h"

#include "../Framework/Framework.h"
#include "Graphics.h"


bool u22::graphics::RectangleRenderer::GenerateLineVAO(void) {
    using Vertex = u22::graphics::ColorVertex;
    // バッファ
    std::uint32_t n = 4;
    std::vector<Vertex> vertices; vertices.resize(n);
    vertices.at(0).position = u22::math::Vector3F(-0.5f, 0.5f, 0.0f); // left top
    vertices.at(1).position = u22::math::Vector3F(-0.5f, -0.5f, 0.0f); // left bottom
    vertices.at(2).position = u22::math::Vector3F(0.5f, -0.5f, 0.0f); // right bottom
    vertices.at(3).position = u22::math::Vector3F(0.5f, 0.5f, 0.0f); // right top

    std::vector<std::uint32_t> indices; indices.reserve(n * 2);
    for (std::uint32_t i = 0; i < n; i++) {
        indices.push_back(i);
        if (i == n - 1) {
            indices.push_back(0);
        } // if
        else {
            indices.push_back(i + 1);
        } // else
    } // for

    if (!_line_vao.Generate<u22::graphics::ColorVertex>(vertices, indices)) {
        _line_vao.Delete();
        return false;
    } // if
    _line_vao.ToLines();
    return true;
}

bool u22::graphics::RectangleRenderer::GenerateFillVAO(void) {
    using Vertex = u22::graphics::ColorVertex;
    // バッファ
    std::vector<Vertex> vertices; vertices.resize(4);
    vertices.at(0).position = u22::math::Vector3F(-0.5f, 0.5f, 0.0f); // left top
    vertices.at(1).position = u22::math::Vector3F(-0.5f, -0.5f, 0.0f); // left bottom
    vertices.at(2).position = u22::math::Vector3F(0.5f, -0.5f, 0.0f); // right bottom
    vertices.at(3).position = u22::math::Vector3F(0.5f, 0.5f, 0.0f); // right top

    std::vector<std::uint32_t> indices; indices.reserve(6);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    if (!_fill_vao.Generate<u22::graphics::ColorVertex>(vertices, indices)) {
        _fill_vao.Delete();
        return false;
    } // if
    _fill_vao.ToTriangles();
    return true;
}

bool u22::graphics::RectangleRenderer::RenderRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera, const u22::graphics::VertexArray& vao) const {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    // flip
    auto pos = rectangle.GetLeftTop();
    pos += rectangle.GetSize() * 0.5f;
    pos.y *= -1.0f;
    auto scale = u22::math::Vector3F(rectangle.GetWidth(), rectangle.GetHeight(), 1.0f);

    auto translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(pos, 0.0f));
    auto rotation = glm::toMat4(glm::quat());
    auto scaling = glm::scale(math::mat4x4::kIdentity, scale);
    auto transform = translation * rotation * scaling;


    shader->Enable();
    shader->TransferUniform("uniform_color", color);
    shader->TransferUniform("model_transform", transform);
    shader->TransferUniform("view_projection", camera.GetViewProjectionMatrix());

    // 描画
    vao.Bind();
    vao.DrawElements();
    shader->Disable();
    vao.UnBind();
    return true;
}

u22::graphics::RectangleRenderer::RectangleRenderer() :
    _line_vao(),
    _fill_vao(),
    _shader() {
}

u22::graphics::RectangleRenderer::~RectangleRenderer() {
}

bool u22::graphics::RectangleRenderer::Initialize(void) {
    auto shader = u22::Framework::GetInfomation()->graphics->GetEffectShader(u22::graphics::EffectShaderType::Rectangle);
    if (!shader) {
        return false;
    } // if
    _shader = shader;

    if (!this->GenerateLineVAO()) {
        return false;
    } // if
    if (!this->GenerateFillVAO()) {
        return false;
    } // if
    return true;
}

bool u22::graphics::RectangleRenderer::RenderLineRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    return this->RenderRectangle(rectangle, color, camera, _line_vao);
}

bool u22::graphics::RectangleRenderer::RenderFillRectangle(const u22::shape::Rectangle& rectangle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    return this->RenderRectangle(rectangle, color, camera, _fill_vao);
}

bool u22::graphics::RectangleRenderer::Release(void) {
    _shader.reset();
    _fill_vao.Delete();
    _line_vao.Delete();
    return true;;
}