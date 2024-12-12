/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Type
*/

#pragma once

#include <ostream>

#include "tools.hpp"

namespace Rtype::Client {
struct Type {
  ObjectType _type;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Type &type);
