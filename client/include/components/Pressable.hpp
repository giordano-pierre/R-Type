/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Pressable
*/

#pragma once

#include "ECS/ECS.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace rtype::client {
struct Pressable {
    Pressable(std::shared_ptr<sf::Texture> texture,
              std::function<void(ECS &, Entity)> press, int link = 0)
        : _texture(texture), _press(press), _link(link){};
    ~Pressable() = default;
    std::shared_ptr<sf::Texture> _texture;
    std::function<void(ECS &, Entity)> _press;
    int _link;

    bool _isPressed = false;
};
} // namespace rtype::client
