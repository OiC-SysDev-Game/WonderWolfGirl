#include "SpriteAnimationController.h"


u22::animation::SpriteAnimationController::SpriteAnimationController() :
    _ideal_frame_time(1.0f / 60.0f),
    _motion_end(false),
    _time(0.0f),
    //_frame(0),
    _current_motion_no(),
    _current_pattern_no(),
    _source_rectangle(),
    _current_aniamtion(),
    _animations() {
}

u22::animation::SpriteAnimationController::~SpriteAnimationController() {
}

void u22::animation::SpriteAnimationController::SetMotionLoop(bool loop) {
    _current_aniamtion->loop = loop;
}

int u22::animation::SpriteAnimationController::GetMotionNo(void) const {
    return this->_current_motion_no;
}

std::uint32_t u22::animation::SpriteAnimationController::GetMotionCount(void) const {
    return this->_animations.size();
}

u22::shape::Rectangle u22::animation::SpriteAnimationController::GetSourceRectangle(void) const {
    auto offset = u22::math::Vector2F(_current_aniamtion->offset_x, _current_aniamtion->offset_y);
    auto size = u22::math::Vector2F(_current_aniamtion->width, _current_aniamtion->height);
    
    auto rect = u22::shape::Rectangle();
    rect.SetBounds(0.0f, 0.0f, size.x, size.y);

    
    rect.Translate(offset);
    rect.Translate(_current_aniamtion->pattern.at(_current_pattern_no).no * size.x,
                   _current_aniamtion->pattern.at(_current_pattern_no).step * size.y);
    return rect;
}

bool u22::animation::SpriteAnimationController::IsEndMotion(void) const {
    if (_current_aniamtion->loop) {
        return false;
    } // if
    return _motion_end;
}

bool u22::animation::SpriteAnimationController::AddTimer(float time) {
    if (_motion_end) {
        return false;
    } // if
    if (_animations.empty()) {
        return false;
    } // if
    _time += time;
    //_frame++;

    float wait_frame = _current_aniamtion->pattern.at(_current_pattern_no).wait;
    if (wait_frame * _ideal_frame_time < _time) {
    //if (wait_frame < _frame) {
        _current_pattern_no++;
        if (_current_pattern_no > _current_aniamtion->pattern.size() - 1) {
            if (_current_aniamtion->loop) {
                _current_pattern_no = 0;
            } // if
            else {
                _current_pattern_no = _current_aniamtion->pattern.size() - 1;
                _motion_end = true;
            } // else
        } // if
        _time = 0.0f;
        //_frame = 0;
    } // if
    return true;
}

bool u22::animation::SpriteAnimationController::ChangeMotion(int no) {
    _motion_end = false;
    //_frame = 0;
    _time = 0.0f;
    _current_pattern_no = 0;

    _current_motion_no = no;
    _current_aniamtion = &_animations.at(no);
    return true;
}

bool u22::animation::SpriteAnimationController::ChangeMotion(const std::string& name) {
    _motion_end = false;
    //_frame = 0;
    _time = 0.0f;
    _current_pattern_no = 0;

    auto it = std::find_if(_animations.begin(), _animations.end(), [&](auto& pair) {
        return pair.second.name == name;
    });
    if (it == _animations.end()) {
        return false;
    } // if

    _current_aniamtion = &(it->second);
    _current_motion_no = it->first;
    return true;
}

bool u22::animation::SpriteAnimationController::Create(u22::animation::SpriteAnimationCreate* data, int size) {
    u22::animation::SpriteAnimationCreate* work = data;
    uint32_t byte_size = sizeof(u22::animation::SpriteAnimationController);

    for (int i = 0; i < size; i++) {
        _animations.emplace(i, work[i]);
    } // for
    _current_aniamtion = &_animations.at(0);
    return true;
}

bool u22::animation::SpriteAnimationController::Create(const std::vector<u22::animation::SpriteAnimationCreate>& data, int size) {
    for (std::uint32_t i = 0; i < data.size(); i++) {
        _animations.emplace(i, data.at(i));
    } // for
    _current_aniamtion = &_animations.at(0);
    return true;
}

bool u22::animation::SpriteAnimationController::Release(void) {
    _animations.clear();
    return true;
}