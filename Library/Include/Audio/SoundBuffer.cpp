#include "SoundBuffer.h"


u22::audio::SoundBuffer::SoundBuffer() :
    _id(),
    _source(),
    _file(),
    _loop(false),
    _end(false) {
}

u22::audio::SoundBuffer::~SoundBuffer() {
}

void u22::audio::SoundBuffer::SetVolume(float volume) {
    _ASSERT_EXPR(_source != NULL, L"SoundBuffer‚ª“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚Ü‚¹‚ñ");
    ::alSourcef(_source, AL_GAIN, volume);
}

void u22::audio::SoundBuffer::SetPitch(float pitch) {
    _ASSERT_EXPR(_source != NULL, L"SoundBuffer‚ª“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚Ü‚¹‚ñ");
    ::alSourcef(_source, AL_PITCH, pitch);
}

void u22::audio::SoundBuffer::SetLoop(bool loop) {
    this->_loop = loop;
    ::alSourcei(_source, AL_LOOPING, loop);
}

bool u22::audio::SoundBuffer::IsPlay(void) const {
    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool u22::audio::SoundBuffer::IsPause(void) const {
    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool u22::audio::SoundBuffer::IsEnd(void) const {
    return this->_end;
}

bool u22::audio::SoundBuffer::Load(const char* path) {
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

bool u22::audio::SoundBuffer::Update(void) {
    return true;
}

bool u22::audio::SoundBuffer::Release(void) {
    if (_id == NULL) {
        return false;
    } // if
    this->Stop();
    ::alDeleteSources(1, &_source);
    ::alDeleteBuffers(1, &_id);
    _id = NULL;
    _source = NULL;
    return true;
}

bool u22::audio::SoundBuffer::Play(void) {
    if (_source == NULL) {
        return false;
    } // if
    ::alSourcePlay(_source);
    return true;
}

bool u22::audio::SoundBuffer::Pause(void) {
    if (_source == NULL) {
        return false;
    } // if

    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    if (state == AL_PAUSED) {
        return false;
    } // if
    ::alSourcePause(_source);
    return true;
}

bool u22::audio::SoundBuffer::Stop(void) const {
    if (_source == NULL) {
        return false;
    } // if

    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    if (state != AL_STOPPED) {
        ::alSourceStop(_source);
    } // if
    return true;
}
bool u22::audio::SoundBuffer::Rewind(void) {
    if (_source == NULL) {
        return false;
    } // if
    ::alSourceRewind(_source);
    return true;
}