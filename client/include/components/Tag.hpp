/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#pragma once

#include <ostream>

#include "tools.hpp"

namespace Rtype::Client {
    struct Tag {
        ObjectType _type;
        size_t _id = 0;
    };
}
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Tag &type);
