/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Scene.hpp"
#include "components/Window.hpp"
#include "events/CreateEvent.hpp"
#include "events/DeleteEvent.hpp"

namespace rtype::client {
class LifeSys {
  public:
    LifeSys() = default;
    ~LifeSys() = default;

    void operator()(ECS &ecs, const CreationEvent &e_create, SparseArray<Window> &windows);
    void operator()(ECS &ecs, const DeleteEvent &e_del, SparseArray<Scene> &scenes);
};
} // namespace rtype::client
