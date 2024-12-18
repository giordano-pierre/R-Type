/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include <ostream>

#include "ECS/ECS.hpp"
#include "tools.hpp"

namespace Rtype::Client {
struct Hitbox {
    TupleFloat _coefSize;
    bool _display = true;
    TupleFloat _client = {0, 0};
    TupleFloat _server = {0, 0};
    bool _needUpdate = true;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out,
                         const Rtype::Client::Hitbox &hitbox);
