/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#pragma once

#include <ostream>

#include "tools.hpp"

namespace rtype::client {
struct Tag {
    Tag(ObjectType type, size_t id = 0) : _type(type), _id(id) {};
    ~Tag() = default;
    ObjectType _type;
    size_t _id;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out, const rtype::client::Tag &type);
