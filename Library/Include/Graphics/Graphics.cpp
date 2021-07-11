#include "Graphics.h"

#include "../Common/Common.h"
#include "../Utility/GraphicsUtilities.h"


bool u22::graphics::Graphics::Setup(void) {
    if (!::glfwInit()) {
        return false;
    } // if
    ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    ::glfwWindowHint(GLFW_SAMPLES, 0);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // font
    if (::FT_Init_FreeType(&_font)) {
        return false;
    } // if
    return true;
}

bool u22::graphics::Graphics::LoadShader(void) {
    bool ret = false;

    {
        auto shader = std::make_shared<u22::graphics::EffectShader>();
        ret = shader->Load("../Resource/shader/sprite.vert", "../Resource/shader/sprite.frag");
        if (!ret) {
            ret = shader->Load("Resource/shader/sprite.vert", "Resource/shader/sprite.frag");
            if (!ret) {
                return false;
            } // if
        } // if
        _shader_map.emplace(u22::graphics::EffectShaderType::Sprite, shader);
    }
    {
        auto shader = std::make_shared<u22::graphics::EffectShader>();
        ret = shader->Load("../Resource/shader/circle.vert", "../Resource/shader/circle.frag");
        if (!ret) {
            ret = shader->Load("Resource/shader/circle.vert", "Resource/shader/circle.frag");
            if (!ret) {
                return false;
            } // if
        } // if
        _shader_map.emplace(u22::graphics::EffectShaderType::Circle, shader);
    }
    {
        auto shader = std::make_shared<u22::graphics::EffectShader>();
        ret = shader->Load("../Resource/shader/rectangle.vert", "../Resource/shader/rectangle.frag");
        if (!ret) {
            ret = shader->Load("Resource/shader/rectangle.vert", "Resource/shader/rectangle.frag");
            if (!ret) {
                return false;
            } // if
        } // if
        _shader_map.emplace(u22::graphics::EffectShaderType::Rectangle, shader);
    }
    u22::utility::GraphicsUtilities::Setup();
    return true;
}

bool u22::graphics::Graphics::ReleaseShader(void) {
    for (auto& shader : _shader_map) {
        if (!shader.second->Release()) {
            return false;
        } // if
    } // for
    _shader_map.clear();
    return true;
}

u22::graphics::Graphics::Graphics() :
    _initialized(false),
    _shader_map(),
    _font() {
    bool setup = this->Setup();
    _ASSERT_EXPR(setup, L"グラフィックスのセットアップでエラーが起きました");
}

u22::graphics::Graphics::~Graphics() {
}

FT_Library u22::graphics::Graphics::GetFontPtr(void) const {
    return this->_font;
}

std::shared_ptr<u22::graphics::EffectShader> u22::graphics::Graphics::GetEffectShader(u22::graphics::EffectShaderType type) const {
    return this->_shader_map.at(type);
}

void u22::graphics::Graphics::ClearTarget(const u22::math::Vector4F& color, float depth, float stencil) {
    // クリア
    auto& c = color;
    ::glClearColor(c.r, c.g, c.b, c.a);
    ::glClearDepth(depth);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void u22::graphics::Graphics::RenderStart(void) {
    // デフォルトのフレームバッファに対しての操作
    ::glDisable(GL_DEPTH);
    //::glEnable(GL_DEPTH);

    //::glDisable(GL_CULL_FACE);
    ::glEnable(GL_CULL_FACE);
    ::glFrontFace(GL_CCW); // default
    ::glCullFace(GL_BACK); // default

    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool u22::graphics::Graphics::Initialize(const std::shared_ptr<u22::Window>& window) {
    _initialized = false;

    // OpenGL拡張機能チュートリアル
    // https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/extensions.php
    auto error = ::glewInit();
    if (error != GLEW_OK) {
        //std::cout << "error : " << reinterpret_cast<const char*>(::glewGetErrorString(error)) << "\n";
        ::glfwTerminate();
        return false;
    } // if
    if (!GLEW_ARB_vertex_program) {
        return false;
    } // if


    if (!this->LoadShader()) {
        return false;
    } // if
    _initialized = true;
    return _initialized;
}

bool u22::graphics::Graphics::Release(void) {
    u22::utility::GraphicsUtilities::Cleanup();

    ::FT_Done_FreeType(_font);
    _font = nullptr;


    if (!this->ReleaseShader()) {
        return false;
    } // if

    if (!_initialized) {
        return false;
    } // if
    ::glfwTerminate();
    return true;
}