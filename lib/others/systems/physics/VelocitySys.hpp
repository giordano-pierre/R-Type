/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-valentin.nouri
** File description:
** VelocitySys
*/

#pragma once

#include "ecs/management/ECS/ECS.hpp"
#include "ecs/management/SparseArray/SparseArray.hpp"

#include "ecs/implementation/component/Position/Position.hpp"
#include "ecs/implementation/component/Velocity/Velocity.hpp"

#include "ecs/implementation/event/FrameEvent/FrameEvent.hpp"
#include "ecs/implementation/event/InputEvent/InputEvent.hpp"

struct VelocitySys {
  VelocitySys() = default;
  ~VelocitySys() = default;

  auto operator()(ECS &ecs, const FrameEvent &e_frame,
                  SparseArray<Position> &positions,
                  const SparseArray<Velocity> &velocities) -> void;

  auto operator()(ECS &ecs, const InputEvent &e_input,
                  SparseArray<Velocity> &velocities) -> void;
};
