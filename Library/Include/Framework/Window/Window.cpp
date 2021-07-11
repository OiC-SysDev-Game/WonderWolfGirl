#include "Window.h"


u22::Window::Window() :
    _handle(),
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

    if (full_screen) {
        _handle = ::glfwCreateWindow(_width, _height, _title.c_str(), ::glfwGetPrimaryMonitor(), nullptr);
    } // if
    else {
        _handle = ::glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    } // else
    if (!_handle) {
        ::glfwTerminate();
        return false;
    } // if
    ::glfwMakeContextCurrent(_handle);
    ::glfwSetWindowPos(_handle, pos_x, pos_y);
    return true;
}

bool u22::Window::Destroy(void) {
    if (!_handle) {
        return false;
    } // if
    ::glfwDestroyWindow(_handle);
    return true;
}

void u22::Window::Present(void) const {
    ::glfwSwapBuffers(_handle);
}

void u22::Window::PollEvents(void) const {
    ::glfwPollEvents();
}