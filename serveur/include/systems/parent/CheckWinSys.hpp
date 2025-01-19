/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CheckWinSys
*/

#pragma once

#include "Child.hpp"
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "tools.hpp"

namespace rtype::server {

class CheckWinSys {
  public:
    CheckWinSys() = default;
    ~CheckWinSys() = default;

    void operator()(ECS &ecs, const TicEvent &tic_event,
                    const SparseArray<Tag> &tags, SparseArray<Room> &rooms,
                    SparseArray<Stage> &stages, SparseArray<Child> &children);
};

} // namespace rtype::server
