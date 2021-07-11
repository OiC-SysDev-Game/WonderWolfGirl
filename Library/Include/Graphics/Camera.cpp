#include "Camera.h"

#include "Framework/Framework.h"


void u22::graphics::Camera::UpdateOrtho(void) {
    //this->Create2D();
}

void u22::graphics::Camera::UpdatePerspective(void) {
    _view_matrix = glm::lookAt(_position, _target, _up);
    _projection_matrix = glm::perspective(_fovy, _aspect, _near, _far);
    _view_projection = _projection_matrix * _view_matrix;
}

u22::graphics::Camera::Camera() :
    _fovy(::glm::radians(45.0f)),
    _aspect(),
    //_aspect(u22::Framework::GetInfomation()->window->GetWidth() / u22::Framework::GetInfomation()->window->GetHeight()),
    _near(1.0f),
    _far(1000.0f),
    _position(),
    _target(),
    _up(math::Vector3F(0.0f, 1.0f, 0.0f)),
    _view_matrix(),
    _projection_matrix(),
    _view_projection() {
}

u22::graphics::Camera::~Camera() {
}

void u22::graphics::Camera::SetPosition(u22::math::Vector3F pos) {
    this->_position = pos;
}

u22::math::Vector3F u22::graphics::Camera::GetPosition(void) const {
    return this->_position;
}

glm::mat4 u22::graphics::Camera::GetViewMatrix(void) const {
    return this->_view_matrix;
}

glm::mat4 u22::graphics::Camera::GetProjectionMatrix(void) const {
    return this->_projection_matrix;
}

glm::mat4 u22::graphics::Camera::GetViewProjectionMatrix(void) const {
    return this->_view_projection;
}

bool u22::graphics::Camera::Initalize2DCamera(void) {
    _aspect = static_cast<float>(u22::Framework::GetInfomation()->window->GetWidth() / u22::Framework::GetInfomation()->window->GetHeight());

    this->SetPosition(u22::math::Vector3F(0.0f, 0.0f, 0.0f));
    this->Create2D(u22::Framework::GetInfomation()->window->GetWidth(),
                   u22::Framework::GetInfomation()->window->GetHeight());
    // フレームバッファ全体に描画する。左下隅から右上隅へ。
    ::glViewport(0, 0, u22::Framework::GetInfomation()->window->GetWidth(), u22::Framework::GetInfomation()->window->GetHeight()); 
    return true;
}

void u22::graphics::Camera::Update(void) {
    this->UpdatePerspective();
}

void u22::graphics::Camera::Create2D(int width, int height) {
    auto half_size = glm::vec2(width * 0.5f, height * 0.5f);
    auto pos = glm::vec3(glm::vec3(half_size.x + _position.x, -half_size.y - _position.y, 100.0f));
    auto target = glm::vec3(glm::vec3(half_size.x + _position.x, -half_size.y - _position.y, 0.0f));

    _view_matrix = glm::lookAt(pos, target, _up);
    _projection_matrix = glm::ortho(-half_size.x, half_size.x, -half_size.y, half_size.y, _near, _far);

    _view_projection = _projection_matrix * _view_matrix;
}