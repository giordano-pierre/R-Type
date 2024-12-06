/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

#pragma once

#include <ostream>

namespace Rtype::Client {
    struct Playable {
        int _id;
    };
}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Playable &player);
