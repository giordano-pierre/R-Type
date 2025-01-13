/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LifeSys
*/

#pragma once

#include "ECS/ECS.hpp"
#include "Events.hpp"
#include "Components.hpp"

namespace rtype::server {

class LifeSys {
    public:
        LifeSys() = default;
        ~LifeSys() = default;

        void operator()(ECS &ecs, const TicEvent &tic_event,
                        SparseArray<Child> &childrens,
                        const SparseArray<Room> &rooms);
        void operator()(ECS & ecs, const TicEvent &tic_event,
                        SparseArray<Room> &rooms,
                        SparseArray<Stage> &stages,
                        SparseArray<Child> &children);
};

}
