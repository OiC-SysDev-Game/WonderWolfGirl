#include "U22.h"
#include "GameApplicaion.h"


int main(int argc, char* argv[]) {
    auto framework = new u22::Framework();
    auto app = std::make_shared<u22::GameApplication>();
    auto info = u22::ApplicationInfo();
    info.window_width = 1920;
    info.window_height = 1080;
    info.window_position_x = 40;
    info.window_position_y = 40;
    framework->Setup(app, &info);
    int result = framework->Run();
    framework->Cleanup();


    delete framework;
    framework = nullptr;
    return result;
}