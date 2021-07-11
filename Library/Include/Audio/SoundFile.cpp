#include "SoundFile.h"

u22::audio::SoundFile::SoundFile() :
    _file(),
    _info(),
    _data() {
}

u22::audio::SoundFile::~SoundFile() {
}

ALenum u22::audio::SoundFile::GetFormat(void) const {
    switch (_info.channels) {
        case 1:
            return ::alGetEnumValue("AL_FORMAT_MONO16");
        case 2:
            return ::alGetEnumValue("AL_FORMAT_STEREO16");
        default:
            break;
    } // switch
    return ALenum();
}

const void* u22::audio::SoundFile::GetData(void) const {
    return this->_data.data();
}

ALsizei u22::audio::SoundFile::GetSize(void) const {
    return this->_data.size();
}

ALsizei u22::audio::SoundFile::GetFrequency(void) const {
    return this->_info.samplerate;
}

bool u22::audio::SoundFile::Open(const char* path) {
    if (auto format = std::strstr(path, ".wav"); format) {
        _info.format = SF_FORMAT_WAV;
    } // if
    else if (auto format = std::strstr(path, ".ogg"); format) {
        _info.format = SF_FORMAT_OGG;
    } // else if
    else if (auto format = std::strstr(path, ".mp3"); format) {
        _ASSERT_EXPR(false, L"MP3は対応していないフォーマットです");
    } // else if

    // サウンドデータ読み込み
    std::memset(&_info, 0, sizeof(_info));
    _file = ::sf_open(path, SFM_READ, &_info);
    if (!_file) {
        return false;
    } // if
    return true;
}

bool u22::audio::SoundFile::Load(const char* path) {
    if (auto format = std::strstr(path, ".wav"); format) {
        _info.format = SF_FORMAT_WAV;
    } // if
    else if (auto format = std::strstr(path, ".ogg"); format) {
        _info.format = SF_FORMAT_OGG;
    } // else if
    else if (auto format = std::strstr(path, ".mp3"); format) {
        _ASSERT_EXPR(false, L"MP3は対応していないフォーマットです");
    } // else if

    // サウンドデータ読み込み
    std::memset(&_info, 0, sizeof(_info));
    _file = ::sf_open(path, SFM_READ, &_info);
    if (!_file) {
        return false;
    } // if

      // よくわかんないけど２掛けたら動いた
    _data = std::vector<int>(static_cast<int>(_info.frames) * _info.channels * 2);
    ::sf_seek(_file, 0, SF_SEEK_SET);
    auto read = ::sf_readf_short(_file, (short*)_data.data(), _info.frames * _info.channels * 2);
    return true;
}

int u22::audio::SoundFile::Read(int offset, int size) {
    return 0;
}

bool u22::audio::SoundFile::Release(void) {
    ::sf_close(_file);
    _data.clear();
    return true;
}