/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PauseSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "components/Drawable.hpp"
#include "components/Velocity.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"

namespace Rtype::Client {
class PauseSys {
public:
  PauseSys() = default;
  ~PauseSys() = default;

  void operator()(ECS &ecs, const InputEvent &e_input,
                  SparseArray<Drawable> &sprites);

  void operator()(ECS &ecs, const InputEvent &e_input,
                  SparseArray<Velocity> &velocities);
};
} // namespace Rtype::Client
