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
    Tag(ObjectType type, size_t id = 0) : _type(type), _id(id){};
    ~Tag() = default;
    ObjectType _type;
    size_t _id;
};
} // namespace Rtype::Client
std::ostream &operator<<(std::ostream &out, const Rtype::Client::Tag &type);
