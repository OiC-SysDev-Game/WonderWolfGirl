#include "Input.h"


u22::input::Input::Input() :
    _window(),
    _previous_key_status(),
    _current_key_status(),
    _previous_mouse_button_status(),
    _current_mouse_button_status(),
    _mouse_x(),
    _mouse_y() {
    this->AddMouse(MouseButton::Right);
    this->AddMouse(MouseButton::Left);

    this->AddKey(KeyCode::Escape);
    this->AddKey(KeyCode::Space);
    this->AddKey(KeyCode::Up);
    this->AddKey(KeyCode::Down);
    this->AddKey(KeyCode::Right);
    this->AddKey(KeyCode::Left);


    this->AddKey(KeyCode::Enter);
    this->AddKey(KeyCode::Return);
    this->AddKey(KeyCode::Key0);
    this->AddKey(KeyCode::Key1);
    this->AddKey(KeyCode::Key2);
    this->AddKey(KeyCode::Key3);
    this->AddKey(KeyCode::Key4);
    this->AddKey(KeyCode::Key5);
    this->AddKey(KeyCode::Key6);
    this->AddKey(KeyCode::Key7);
    this->AddKey(KeyCode::Key8);
    this->AddKey(KeyCode::Key9);
    this->AddKey(KeyCode::A);
    this->AddKey(KeyCode::B);
    this->AddKey(KeyCode::C);
    this->AddKey(KeyCode::D);
    this->AddKey(KeyCode::E);
    this->AddKey(KeyCode::F);
    this->AddKey(KeyCode::G);
    this->AddKey(KeyCode::H);
    this->AddKey(KeyCode::I);
    this->AddKey(KeyCode::J);
    this->AddKey(KeyCode::K);
    this->AddKey(KeyCode::L);
    this->AddKey(KeyCode::M);
    this->AddKey(KeyCode::N);
    this->AddKey(KeyCode::O);
    this->AddKey(KeyCode::P);
    this->AddKey(KeyCode::Q);
    this->AddKey(KeyCode::R);
    this->AddKey(KeyCode::S);
    this->AddKey(KeyCode::T);
    this->AddKey(KeyCode::U);
    this->AddKey(KeyCode::V);
    this->AddKey(KeyCode::W);
    this->AddKey(KeyCode::X);
    this->AddKey(KeyCode::Y);
    this->AddKey(KeyCode::Z);

    this->AddKey(KeyCode::Right);
    this->AddKey(KeyCode::Left);
    this->AddKey(KeyCode::Up);
    this->AddKey(KeyCode::Down);
    this->AddKey(KeyCode::Space);
    this->AddKey(KeyCode::Escape);
}

u22::input::Input::~Input() {
}

void u22::input::Input::SetWindow(const std::shared_ptr<u22::Window>& ptr) {
    this->_window = ptr;
}

float u22::input::Input::GetMouseX(void) const noexcept {
    return static_cast<float>(this->_mouse_x);
}

float u22::input::Input::GetMouseY(void) const noexcept {
    return static_cast<float>(this->_mouse_y);
}

bool u22::input::Input::IsPush(u22::input::KeyCode keycode) const noexcept {
    return this->IsPush(keycode, _previous_key_status, _current_key_status);
}

bool u22::input::Input::IsPush(u22::input::MouseButton button) const noexcept {
    return this->IsPush(button, _previous_mouse_button_status, _current_mouse_button_status);
}

bool u22::input::Input::IsHold(u22::input::KeyCode keycode) const noexcept {
    return this->IsHold(keycode, _previous_key_status, _current_key_status);
}

bool u22::input::Input::IsHold(u22::input::MouseButton button) const noexcept {
    return this->IsHold(button, _previous_mouse_button_status, _current_mouse_button_status);
}

bool u22::input::Input::IsPull(u22::input::KeyCode keycode) const noexcept {
    return this->IsPull(keycode, _previous_key_status, _current_key_status);
}

bool u22::input::Input::IsPull(u22::input::MouseButton button) const noexcept {
    return this->IsHold(button, _previous_mouse_button_status, _current_mouse_button_status);
}

bool u22::input::Input::AddKey(u22::input::KeyCode keycode) {
    if (this->Contain(keycode, _previous_key_status) || this->Contain(keycode, _current_key_status)) {
        return false;
    } // if

    _previous_key_status.emplace(keycode, 0);
    _current_key_status.emplace(keycode, 0);
    return true;

}

bool u22::input::Input::AddMouse(u22::input::MouseButton button) {
    if (this->Contain(button, _previous_mouse_button_status) || this->Contain(button, _current_mouse_button_status)) {
        return false;
    } // if

    _previous_mouse_button_status.emplace(button, 0);
    _current_mouse_button_status.emplace(button, 0);
    return true;
}

void u22::input::Input::Refresh(void) {
    if (auto window = _window.lock()) {
        ::glfwGetCursorPos(window->GetHandle(), &_mouse_x, &_mouse_y);
        _mouse_x = std::clamp(static_cast<int>(_mouse_x), 0, window->GetWidth());
        _mouse_y = std::clamp(static_cast<int>(_mouse_y), 0, window->GetHeight());

        _previous_key_status = _current_key_status;
        for (auto& state : _current_key_status) {
            state.second = ::glfwGetKey(window->GetHandle(), input::ToRawCode(state.first));
        } // for

        _previous_mouse_button_status = _current_mouse_button_status;
        for (auto& state : _current_mouse_button_status) {
            state.second = ::glfwGetMouseButton(window->GetHandle(), input::ToRawCode(state.first));
        } // for
    } // if
}