/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Selectable
*/
#pragma once

#include "ECS/ECS.hpp"
#include "tools.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace rtype::client {
struct Selectable {
    Selectable(std::shared_ptr<sf::Texture>, std::function<void(ECS &, Entity)>,
               std::function<void(ECS &, Entity)>);
    ~Selectable() = default;
    std::shared_ptr<sf::Texture> _texture;
    std::function<void(ECS &, Entity)> _sel;
    std::function<void(ECS &, Entity)> _desel;

    sf::Sprite _sprite;
    TupleUInt _size;
    bool _isSelected = false;
    bool _display = false;
};
} // namespace rtype::client
