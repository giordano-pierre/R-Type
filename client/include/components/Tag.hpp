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
    Tag(ObjectType type, std::string id = "") : _type(type), _id(id){};
    ~Tag() = default;
    ObjectType _type;
    std::string _id;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out, const rtype::client::Tag &type);
