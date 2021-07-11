#include "CircleRenderer.h"

#include "../Framework/Framework.h"
#include "Graphics.h"


bool u22::graphics::CircleRenderer::GenerateLineVAO(void) {
    using Vertex = u22::graphics::ColorVertex;
    // バッファ
    std::uint32_t n = 256;
    std::vector<Vertex> vertices; vertices.reserve(n);
    std::vector<std::uint32_t> indices; indices.reserve(n);
    for (std::uint32_t i = 0; i <= n; i++) {
        float rate = static_cast<float>(i) / static_cast<float>(n);
        auto pos = u22::math::Vector2F(std::cosf(2.0f * u22::math::def::kPi * rate),
                                       std::sinf(2.0f * u22::math::def::kPi * rate));
        // 作成
        auto vert = Vertex();
        vert.position = glm::vec3(pos.x, pos.y, 0.0f);
        vertices.push_back(vert);
        indices.push_back(i);
    } // for

    if (!_line_vao.Generate<u22::graphics::ColorVertex>(vertices, indices)) {
        _line_vao.Delete();
        return false;
    } // if
    _line_vao.ToLineStrip();
    return true;
}

bool u22::graphics::CircleRenderer::GenerateFillVAO(void) {
    using Vertex = u22::graphics::ColorVertex;
    
    std::vector<Vertex> vertices;
    vertices.reserve(256 + 1);
    std::vector<uint32_t> indices;

    vertices.push_back(Vertex());
    for (uint32_t i = 1, n = 256 + 1; i <= n + 1; i++) {
        float rate = static_cast<float>(i) / static_cast<float>(n);
        auto pos = glm::vec2(std::cosf(2.0f * u22::math::def::kPi * rate),
                             std::sinf(2.0f * u22::math::def::kPi * rate));
        // 頂点作成
        auto vert = Vertex();
        vert.position = glm::vec3(pos.x, pos.y, 0.0f);
        vertices.push_back(vert);
        indices.push_back(0);
        indices.push_back(i);
    } // for

    if (!_fill_vao.Generate<u22::graphics::ColorVertex>(vertices, indices)) {
        _fill_vao.Delete();
        return false;
    } // if
    _fill_vao.ToTriangleStrip();
    return true;
}

bool u22::graphics::CircleRenderer::RenderCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera, const u22::graphics::VertexArray& vao) const {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    // flip
    auto pos = circle.position;
    pos.y *= -1.0f;

    auto translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(pos, 0.0f));
    auto transform = translation;
    // セット
    shader->Enable();

    shader->TransferUniform("uniform_radius", circle.radius);
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

u22::graphics::CircleRenderer::CircleRenderer() :
    _line_vao(),
    _fill_vao(),
    _shader() {
}

u22::graphics::CircleRenderer::~CircleRenderer() {
}

bool u22::graphics::CircleRenderer::Initialize(void) {
    auto shader = u22::Framework::GetInfomation()->graphics->GetEffectShader(u22::graphics::EffectShaderType::Circle);
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

bool u22::graphics::CircleRenderer::RenderLineCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    return this->RenderCircle(circle, color, camera, _line_vao);
}

bool u22::graphics::CircleRenderer::RenderFillCircle(const u22::shape::Circle& circle, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
    return this->RenderCircle(circle, color, camera, _fill_vao);
}

bool u22::graphics::CircleRenderer::Release(void) {
    _shader.reset();
    _fill_vao.Delete();
    _line_vao.Delete();
    return true;;
}
