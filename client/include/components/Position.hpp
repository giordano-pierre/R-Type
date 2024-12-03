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
        TupleFloat _old;
        TupleFloat _current;
    };

}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Position &position);
