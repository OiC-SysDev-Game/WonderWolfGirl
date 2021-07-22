#include "Window.h"


u22::Window::Window() :
    _handle(),
    _monitor(),
    _title(),
    _width(),
    _height() {
}

u22::Window::~Window() {
}

void u22::Window::SetHandle(::GLFWwindow* ptr) {
    this->_handle = ptr;
}

::GLFWwindow* u22::Window::GetHandle(void) {
    return this->_handle;
}

int u22::Window::GetWidth(void) const {
    return this->_width;
}

int u22::Window::GetHeight(void) const {
    return this->_height;
}

bool u22::Window::ShouldClose(void) {
    return ::glfwWindowShouldClose(_handle);
}

bool u22::Window::Create(const char* title, int width, int height, int pos_x, int pos_y, bool full_screen) {
    _title = title;
    _width = width;
    _height = height;
    _monitor = ::glfwGetPrimaryMonitor();

    auto mode = ::glfwGetVideoMode(_monitor);

    // test
    //RECT window_rect = RECT{ 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
    //::AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, FALSE);
    //int actual_width = window_rect.right - window_rect.left;
    //int actual_height = window_rect.bottom - window_rect.top;
    //int actual_x = std::max<int>(0, (mode->width - actual_width) / 2);
    //int actual_y = std::max<int>(0, (mode->height - actual_height) / 2);
    //int diff_x = actual_width - width;
    //int diff_y = actual_height - height;


    if (full_screen) {
        _handle = ::glfwCreateWindow(_width, _height, _title.c_str(), _monitor, nullptr);
        ::glfwSetWindowMonitor(_handle, _monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } // if
    else {
        _handle = ::glfwCreateWindow(_width, _height , _title.c_str(), nullptr, nullptr);
    } // else

    if (!_handle) {
        ::glfwTerminate();
        return false;
    } // if
    ::glfwMakeContextCurrent(_handle);
    ::glfwSetWindowPos(_handle, pos_x, pos_y);
    ::glfwShowWindow(_handle);
    return true;
}

bool u22::Window::Destroy(void) {
    if (!_handle) {
        return false;
    } // if
    ::glfwDestroyWindow(_handle);
    return true;
}

void u22::Window::Close(void) const {
    glfwSetWindowShouldClose(_handle, 1);
}

void u22::Window::Present(void) const {
    ::glfwSwapBuffers(_handle);
}

void u22::Window::PollEvents(void) const {
    ::glfwPollEvents();
}