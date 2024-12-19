/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

#pragma once

#include <ostream>

namespace rtype::client {
struct Playable {
    Playable(int id) : _id(id){};
    ~Playable() = default;
    int _id;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Playable &player);
