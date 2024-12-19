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
    Playable(int id, std::string name = "Player 1") : _id(id), _name(name) {};
    ~Playable() = default;
    int _id;
    std::string _name;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Playable &player);
