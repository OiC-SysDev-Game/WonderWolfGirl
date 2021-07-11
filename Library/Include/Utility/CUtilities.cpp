#include "CUtilities.h"

#include <random>

#include "../Framework/Framework.h"


float u22::utility::CUtilities::GetFrameSecond(void) {
    return u22::Framework::GetInfomation()->clock->GetFrameSecond();
}

float u22::utility::CUtilities::GetFPS(void) {
    return u22::Framework::GetInfomation()->clock->GetFPS();
}

int u22::utility::CUtilities::GenerateRandom(int min, int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return random(engine);
}

float u22::utility::CUtilities::GenerateRandomF(float min, float max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_real_distribution<> random(min, max);
    return static_cast<float>(random(engine));
}