/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound
*/

#include "components/Sound.hpp"
#include <stdexcept>

namespace rtype::client {

Sound::Sound(const std::string &filePath, SoundState state, float volume)
    : _music(std::make_shared<sf::Music>()), _state(state), _volume(volume) {
    if (!_music->openFromFile(filePath)) {
        throw std::runtime_error("Failed to load music file: " + filePath);
    }
    _music->setVolume(_volume);

    if (_state == SoundState::LOOP) {
        _music->setLoop(true);
        _music->play();
    } else if (_state == SoundState::PLAY_ONCE) {
        _music->play();
    }
}

std::ostream &operator<<(std::ostream &out, const Sound &sound) {
    out << "Sound: Volume = " << sound._volume
        << ", State = " << static_cast<int>(sound._state);
    return out;
}

} // namespace rtype::client
