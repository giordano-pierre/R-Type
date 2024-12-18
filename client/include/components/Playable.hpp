/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

#pragma once

#include <ostream>

namespace Rtype::Client {
struct Playable {
  Playable(int id) : _id(id) {};
  ~Playable() = default;
  int _id;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Playable &player);
