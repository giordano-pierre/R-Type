/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Scene
*/

#pragma once

#include "tools.hpp"

namespace rtype::client {
struct Scene {
    Scene(SceneType type) : _type(type) {};
    ~Scene() = default;
    SceneType _type;
};
} // namespace rtype::client
