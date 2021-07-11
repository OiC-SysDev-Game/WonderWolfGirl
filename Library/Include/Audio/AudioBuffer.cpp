#include "AudioBuffer.h"


u22::audio::AudioBuffer::AudioBuffer() :
    _id(),
    _source(),
    _file() {
}

u22::audio::AudioBuffer::~AudioBuffer() {
}

ALuint u22::audio::AudioBuffer::GetID(void) const {
    return this->_id;
}

bool u22::audio::AudioBuffer::IsEnable(void) const {
    return _id != NULL;
}

bool u22::audio::AudioBuffer::Generate(void) {
    ::alGenBuffers(1, &_id);
    if (_id == NULL) {
        return false;
    } // if
    return true;
}

bool u22::audio::AudioBuffer::Delete(void) {
    if (_id != NULL) {
        return false;
    } // if
    ::alDeleteBuffers(1, &_id);
    return true;
}
/*
bool u22::audio::AudioBuffer::Load(const char* path) {
    ::alGenBuffers(1, &_id);
    if (!_file.Load(path)) {
        return false;
    } // if

    ::alBufferData(_id, _file.GetFormat(), _file.GetData(), _file.GetSize(), _file.GetFrequency());
    if (::alGetError() != AL_NO_ERROR) {
        return false;
    } // if

    ::alGenSources(1, &_source);
    ::alSourcei(_source, AL_BUFFER, _id);

    _file.Release();
    return true;
}

bool u22::audio::AudioBuffer::Release(void) {
    if (_id == NULL) {
        return false;
    } // if
    ::alSourceStop(_source);
    ::alDeleteSources(1, &_source);
    ::alDeleteBuffers(1, &_id);
    _id = NULL;
    _source = NULL;
    return true;
}

bool u22::audio::AudioBuffer::Play(void) const {
    if (_source == NULL) {
        return false;
    }
    alSourcePlay(_source);
    return true;
}
*/