#include "IApplicaion.h"

//#include <chrono>
//#include <iomanip>
//#include <iostream>
#include <filesystem>


bool u22::IApplicaion::SetCurrentPath(const char* name) {
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

u22::IApplicaion::IApplicaion() {
}

u22::IApplicaion::~IApplicaion() {
}