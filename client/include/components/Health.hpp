/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Health
*/

#pragma once

namespace rtype::client {

struct Health {
  public:
    Health(int health) : _health(health){};

    int _health;
};

} // namespace rtype::client
