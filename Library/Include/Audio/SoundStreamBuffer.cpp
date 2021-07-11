#include "SoundStreamBuffer.h"

#include <iostream>


void u22::audio::SoundStreamBuffer::Loop(void) {
    _position = 0;
    _eof = false;
    _current = 0;
    _next = 1;

    for (auto& work : _buffers) {
        ::alSourceUnqueueBuffers(_source, 1, &work);
    } // for
    for (auto& work : _buffers) {
        auto buffer = this->WhiteNextData(work);
        ::alSourceQueueBuffers(_source, 1, &buffer);
    } // for
    ::alSourcePlay(_source);
}

ALuint u22::audio::SoundStreamBuffer::WhiteNextData(ALuint buffer) {
    if (buffer == NULL) {
        ::alGenBuffers(1, &buffer);
    } // if
    auto& data = _stream_buffers[_next];

    ::sf_seek(_file, _position, SF_SEEK_SET);
    auto read = ::sf_readf_short(_file, (short*)data.data(), _buffer_size);
    _position += read;

    ALsizei byte_size = static_cast<int>(read) * _info.channels * _byte_size_coefficient;
    ::alBufferData(buffer, _format, data.data(), byte_size, 44100);
    std::swap(_current, _next);
    return buffer;
}

u22::audio::SoundStreamBuffer::SoundStreamBuffer() :
    _source(),
    _buffers(),
    _file(),
    _info(),
    _stream_buffers(),
    _position(),
    _eof(false),
    _current(0),
    _next(1),
    _end(false),
    _buffer_size(),
    _format(),
    _byte_size_coefficient(sizeof(int) / sizeof(short)),
    _loop(false) {
}

u22::audio::SoundStreamBuffer::~SoundStreamBuffer() {
}

void u22::audio::SoundStreamBuffer::SetVolume(float volume) {
    _ASSERT_EXPR(_source != NULL, L"SoundStreamBufferが読み込まれていません");
    ::alSourcef(_source, AL_GAIN, volume);
}

void u22::audio::SoundStreamBuffer::SetPitch(float pitch) {
    _ASSERT_EXPR(_source != NULL, L"SoundStreamBufferが読み込まれていません");
    ::alSourcef(_source, AL_PITCH, pitch);
}

void u22::audio::SoundStreamBuffer::SetLoop(bool loop) {
    this->_loop = loop;
}

bool u22::audio::SoundStreamBuffer::IsPlay(void) const {
    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool u22::audio::SoundStreamBuffer::IsPause(void) const {
    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool u22::audio::SoundStreamBuffer::IsEnd(void) const {
    return this->_end;
}

bool u22::audio::SoundStreamBuffer::Load(const char* path) {
    if (auto format = std::strstr(path, ".wav"); format) {
        _info.format = SF_FORMAT_WAV;
    } // if
    else if (auto format = std::strstr(path, ".ogg"); format) {
        _info.format = SF_FORMAT_OGG;
    } // else if

    // サウンドデータ読み込み
    std::memset(&_info, 0, sizeof(_info));
    _file = ::sf_open(path, SFM_READ, &_info);
    if (!_file) {
        return false;
    } // if
    if (_info.channels == 1) {
        _format = AL_FORMAT_MONO16;
    } // if
    else if (_info.channels == 2) {
        _format = AL_FORMAT_STEREO16;
    } // else if

    // ボイス作成
    ::alGenSources(1, &_source);
    _buffer_size = _info.channels * _byte_size_coefficient * _info.samplerate;

    for (auto& data : _stream_buffers) {
        data.resize(_buffer_size);
    } // for

    for (auto& work : _buffers) {
        auto buffer = this->WhiteNextData(work);
        ::alSourceQueueBuffers(_source, 1, &buffer);
    } // for
    return true;
}

bool u22::audio::SoundStreamBuffer::Update(void) {
    int processed;
    ::alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);

    if (!_eof && processed >= static_cast<int>(_buffers.size()) - 1) {
        if (_position >= _info.frames) {
            _eof = true;
        } // if
        else {
            ::alSourceUnqueueBuffers(_source, 1, &_buffers[_current]);
            auto buffer = this->WhiteNextData(_buffers[_current]);
            ::alSourceQueueBuffers(_source, 1, &buffer);
        } // else
    } // if
    // バッファが0で再生終了
    if (processed == _buffers.size()) {
        if (_loop) {
            this->Loop();
        } // if
        else {
            _end = true;
        } // else
    } // if
    return true;
}

bool u22::audio::SoundStreamBuffer::Release(void) {
    ::sf_close(_file);
    _stream_buffers->clear();

    ::alSourceStop(_source);
    ::alDeleteSources(1, &_source);
    ::alDeleteBuffers(2, _buffers.data());

    *_buffers.data() = NULL;
    _source = NULL;
    return true;
}

bool u22::audio::SoundStreamBuffer::Play(void) {
    if (_source == NULL) {
        return false;
    } // if

    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING) {
        return false;
    } // if

    ::alSourcePlay(_source);
    return true;
}

bool u22::audio::SoundStreamBuffer::Pause(void) {
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

bool u22::audio::SoundStreamBuffer::Stop(void) const {
    if (_source == NULL) {
        return false;
    } // if

    ALint state = 0;
    ::alGetSourcei(_source, AL_SOURCE_STATE, &state);
    if (state == AL_STOPPED) {
        return false;
    } // if

    ::alSourcePause(_source);
    return true;
}

bool u22::audio::SoundStreamBuffer::Rewind(void) {
    if (_source == NULL) {
        return false;
    } // if
    _position = 0;
    ::alSourceRewind(_source);
    return true;
}