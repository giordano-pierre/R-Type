/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#pragma once

#include <ostream>

#include "tools.hpp"

namespace rtype::client {
struct Position {
    Position(float x, float y, TupleFloat client = {0, 0},
             bool needUpdate = true)
        : _server({x, y}), _client(client), _needUpdate(needUpdate){};
    ~Position() = default;
    TupleFloat _server;
    TupleFloat _client;
    bool _needUpdate;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Position &position);
