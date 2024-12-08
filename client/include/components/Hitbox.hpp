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
    };
}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Hitbox &hitbox);
