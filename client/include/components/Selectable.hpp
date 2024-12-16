/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Selectable
*/
#pragma once

#include "ECS/ECS.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace Rtype::Client {
struct Selectable {
  std::shared_ptr<sf::Texture> _texture;
  std::function<void(ECS &)> _func;
  bool _isSelected = false;
};
} // namespace Rtype::Client
