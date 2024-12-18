/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#pragma once

#include "tools.hpp"

#include <ostream>

namespace Rtype::Client {
struct Velocity {
  Velocity(int x, int y) : _current({x, y}){};
  ~Velocity() = default;

  TupleInt _current;
  bool _activated = true;
};
} // namespace Rtype::Client

std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Velocity &position);
