/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"
#include "components/Velocity.hpp"
#include "components/Position.hpp"
#include "components/Playable.hpp"
#include "components/Drawable.hpp"

namespace Rtype::Client {
    class VelocitySys {
        public:
            VelocitySys() = default;
            ~VelocitySys() = default;

        void operator()(ECS &ecs, const InputEvent &e_input,
                        const SparseArray<Playable> &players,
                        SparseArray<Velocity> &velocities);

        void operator()(ECS &ecs, const TicEvent &e_tic,
                        SparseArray<Position> &positions,
                        const SparseArray<Velocity> &velocities);

    };
}
