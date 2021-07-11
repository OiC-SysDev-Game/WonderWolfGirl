#ifndef U22_INPUT_KEYCODE_H
#define U22_INPUT_KEYCODE_H


#include <type_traits>

#include "../Common/Common.h"


namespace u22::input {
// glfw keycode
enum class KeyCode : int {
    Return = GLFW_KEY_ENTER,
    Enter = KeyCode::Return,
    Key0 = GLFW_KEY_0,
    Key1 = GLFW_KEY_1,
    Key2 = GLFW_KEY_2,
    Key3 = GLFW_KEY_3,
    Key4 = GLFW_KEY_4,
    Key5 = GLFW_KEY_5,
    Key6 = GLFW_KEY_6,
    Key7 = GLFW_KEY_7,
    Key8 = GLFW_KEY_8,
    Key9 = GLFW_KEY_9,
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    Right = GLFW_KEY_RIGHT,
    Left = GLFW_KEY_LEFT,
    Up = GLFW_KEY_UP,
    Down = GLFW_KEY_DOWN,
    Space = GLFW_KEY_SPACE,
    Escape = GLFW_KEY_ESCAPE,
    CountMax,
};
enum class MouseButton : int {
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Left = GLFW_MOUSE_BUTTON_LEFT,
};
static int ToRawCode(const u22::input::KeyCode code) noexcept {
    return static_cast<std::underlying_type<u22::input::KeyCode>::type>(code);
}
static int ToRawCode(const u22::input::MouseButton code) noexcept {
    return static_cast<std::underlying_type<u22::input::MouseButton>::type>(code);
}

}
#endif // !U22_INPUT_KEYCODE_H