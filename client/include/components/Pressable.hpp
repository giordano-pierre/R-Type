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

namespace Rtype::Client {
struct Pressable {
  Pressable(std::shared_ptr<sf::Texture> texture, std::function<void(ECS &, Entity)> press)
    : _texture(texture), _press(press) {};
  ~Pressable() = default;
  std::shared_ptr<sf::Texture> _texture;
  std::function<void(ECS &, Entity)> _press;

  bool _isPressed = false;
};
} // namespace Rtype::Client
