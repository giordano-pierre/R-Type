/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Hitbox.hpp"
#include "components/Playable.hpp"
#include "components/Position.hpp"
#include "components/Window.hpp"
#include "events/InputEvent.hpp"

namespace Rtype::Client {
class ShootSys {
public:
  ShootSys() = default;
  ~ShootSys() = default;

  void operator()(ECS &ecs, const InputEvent &e_input,
                  SparseArray<Window> &windows,
                  const SparseArray<Playable> &players,
                  const SparseArray<Position> &positions,
                  const SparseArray<Hitbox> &hitboxs);
};
} // namespace Rtype::Client