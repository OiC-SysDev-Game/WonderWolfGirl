#include "Audio.h"

u22::audio::Audio::Audio() :
    _device(),
    _context() {
}

u22::audio::Audio::~Audio() {
}

bool u22::audio::Audio::Initialize(void) {
    _device = ::alcOpenDevice(nullptr);
    if (!_device) {
        return false;
    } // if
    _context = ::alcCreateContext(_device, NULL);
    if (!_context) {
        return false;
    } // if
    ::alcMakeContextCurrent(_context);
    return true;
}

bool u22::audio::Audio::Release(void) {
    if (!_context || !_device) {
        return false;
    } // if
    ::alcMakeContextCurrent(nullptr);
    ::alcDestroyContext(_context);
    ::alcCloseDevice(_device);
    _device = nullptr;
    _context = nullptr;
    return true;
}