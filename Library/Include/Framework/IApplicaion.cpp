#include "IApplicaion.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <filesystem>


void u22::IApplicaion::SetCurrentPath(const char* name){
    std::filesystem::path default_path = std::filesystem::current_path();
    auto current_path = default_path.parent_path();
    //auto current_path = default_path;
    current_path.append(name);
    std::filesystem::current_path(current_path);
}
/*
void u22::IApplicaion::PutLocalTime(void) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::cout << std::ctime(&time) << std::endl;
}
*/
u22::IApplicaion::IApplicaion() {
}

u22::IApplicaion::~IApplicaion() {
}