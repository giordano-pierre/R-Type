/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#pragma once

#include <ostream>

#include "enums.hpp"
#include "tools.hpp"

namespace rtype::client {
struct Tag {
    Tag(EntityType type = OTHER, std::string id = "") : _type(type), _id(id){};
    ~Tag() = default;
    EntityType _type;
    std::string _id;
};
} // namespace rtype::client
std::ostream &operator<<(std::ostream &out, const rtype::client::Tag &type);
