/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PressButtonSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/InputEvent.hpp"
#include "components/Selectable.hpp"
#include "components/Position.hpp"
#include "components/Hitbox.hpp"

namespace Rtype::Client {
    class PressButtonSys {
        public:
            PressButtonSys() = default;
            ~PressButtonSys() = default;

            void operator()(ECS &ecs, const InputEvent &e_input,
                            const SparseArray<Position> &positions,
                            const SparseArray<Hitbox> &hitboxs,
                            SparseArray<Selectable> &selectables);

    };
}
