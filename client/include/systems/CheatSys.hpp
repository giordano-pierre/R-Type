/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CheatSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Window.hpp"
#include "events/InputEvent.hpp"

namespace rtype::client {
class CheatSys {
  public:
    CheatSys() = default;
    ~CheatSys() = default;

    void operator()(ECS &ecs, const InputEvent &e_input,
                    SparseArray<Window> &windows);
};
} // namespace rtype::client
