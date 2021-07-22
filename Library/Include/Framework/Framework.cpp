#include "Framework.h"

#include <filesystem>


u22::FrameworkInfo u22::Framework::_infomation;


bool u22::Framework::SetCurrentPath(const char* name) {
    std::filesystem::path default_path = std::filesystem::current_path();
    if (auto work = default_path.parent_path(); true) {
        work.append(name);
        if (std::filesystem::exists(work)) {
            std::filesystem::current_path(work);
            return true;
        } // if
    } // if

    auto current_path = default_path;
    current_path.append(name);
    if (std::filesystem::exists(current_path) && std::filesystem::is_directory(current_path)) {
        std::filesystem::current_path(current_path);
        return true;
    } // if
    return false;
}

u22::FrameworkInfo* u22::Framework::GetInfomation(void) {
    return &_infomation;
}

u22::Framework::Framework() :
    _clock(std::make_shared<u22::clock::Clock>()),
    _window(std::make_shared<u22::Window>()),
    _input(std::make_shared<u22::input::Input>()),
    _graphics(std::make_shared<u22::graphics::Graphics>()),
    _audio(std::make_shared<u22::audio::Audio>()),
    _applicaion() {

    _input->SetWindow(_window);
    _infomation.clock = _clock;
    _infomation.window = _window;
    _infomation.input = _input;
    _infomation.graphics = _graphics;
    _infomation.audio = _audio;
}

u22::Framework::~Framework() {
}

bool u22::Framework::Setup(const std::shared_ptr<u22::IApplicaion>& ptr, u22::ApplicationInfo* info) {
    SetCurrentPath("Resource");

    // ウインドウ
    if (!_window->Create("None", info->window_width, info->window_height, info->window_position_x, info->window_position_y, info->full_screen_mode)) {
        return false;
    } // if
    // グラフィクス
    if (!_graphics->Initialize(_window)) {
        return false;
    } // if
    // オーディオ
    if (!_audio->Initialize()) {
        return false;
    } // if

    _applicaion = ptr;
    _applicaion->Initialize();
    return true;
}

int u22::Framework::Run(void) {
    while (!_window->ShouldClose()) {
        _clock->Tick();
        if (!_clock->IsFull()) {
            _clock->Wait(); continue;
        } // if
        _clock->Update();

        _input->Refresh();
        _applicaion->Update();
        _applicaion->Render();

        _window->Present();
        _window->PollEvents();
    } // while
    return 0;
}

bool u22::Framework::Cleanup(void) {
    _applicaion->Release();

    _window->Destroy();
    _graphics->Release();
    _audio->Release();
    return true;
}

void u22::Framework::WindowClose(void) const {
    _window->Close();
}