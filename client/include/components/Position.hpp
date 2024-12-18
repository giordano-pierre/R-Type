/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#pragma once

#include <ostream>

#include "tools.hpp"

namespace Rtype::Client {
struct Position {
    TupleFloat _server;
    TupleFloat _client = {0, 0};
    bool _needUpdate = true;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Position &position);
