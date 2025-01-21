/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

#pragma once

#include <ostream>

#include "ECS/ECS.hpp"
#include "clientTools.hpp"

namespace rtype::client {
struct Hitbox {
    Hitbox(TupleFloat, bool = true, TupleFloat = {0, 0}, TupleFloat = {0, 0},
           bool = true);
    ~Hitbox() = default;
    TupleFloat _coefSize;
    bool _display;
    TupleFloat _client;
    TupleFloat _server;
    bool _needUpdate;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Hitbox &hitbox);
