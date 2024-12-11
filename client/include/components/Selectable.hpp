/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Selectable
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include "ECS/ECS.hpp"

namespace Rtype::Client {
    struct Selectable {
        std::shared_ptr<sf::Texture> _texture;
        std::function<void(ECS &)> _func;
        bool _isSelected = false;
    };
}
