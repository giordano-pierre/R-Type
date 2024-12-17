/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PressButtonSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Hitbox.hpp"
#include "components/Position.hpp"
#include "components/Pressable.hpp"
#include "components/Selectable.hpp"
#include "events/InputEvent.hpp"

namespace Rtype::Client {
class PressButtonSys {
public:
  PressButtonSys() = default;
  ~PressButtonSys() = default;

  void operator()(ECS &ecs, const InputEvent &e_input,
                  const SparseArray<Position> &positions,
                  const SparseArray<Hitbox> &hitboxs,
                  const SparseArray<Selectable> &selectables,
                  SparseArray<Pressable> &pressables);
  void operator()(ECS &ecs, const InputEvent &e_input,
                  const SparseArray<Selectable> &selectables,
                  SparseArray<Pressable> &pressables);
};
} // namespace Rtype::Client
