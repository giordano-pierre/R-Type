/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InputEvent
*/
#pragma once

#include <SFML/Window.hpp>

#include "tools.hpp"

namespace rtype::client {
struct InputEvent {
    sf::Event _event;
    UserInput _myEvent;
};
} // namespace rtype::client
