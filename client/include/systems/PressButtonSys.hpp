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

namespace Rtype::Client {
    class PressButtonSys {
        public:
            PressButtonSys() = default;
            ~PressButtonSys() = default;

            void operator()(ECS &ecs, const InputEvent &e_input,
                            SparseArray<Selectable> &selectables);

    };
}
