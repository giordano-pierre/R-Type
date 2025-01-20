/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#pragma once

#include "clientTools.hpp"

#include <ostream>

namespace rtype::client {
struct Velocity {
    Velocity(int x, int y) : _current({x, y}){};
    ~Velocity() = default;

    TupleInt _current;
    bool _activated = true;
};
} // namespace rtype::client

std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Velocity &position);
