/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sound
*/

#pragma once

#include <SFML/Audio.hpp>
#include <memory>
#include <ostream>
#include <string>

namespace rtype::client {

enum class SoundState { LOOP, PLAY_ONCE, TRIGGER };

struct Sound {
    Sound(const std::string &filePath, SoundState state, float volume);
    ~Sound() = default;

    std::shared_ptr<sf::Music> _music;
    SoundState _state;
    float _volume;
};

std::ostream &operator<<(std::ostream &out, const Sound &sound);

} // namespace rtype::client
