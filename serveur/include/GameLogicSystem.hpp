/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLogicSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"

namespace rtype::server::systems {
class GameLogicSys {

  public:
    GameLogicSys() = default;
    ~GameLogicSys() = default;

    void operator()(ECS &ecs, const TicEvent &, SparseArray<Basics> &basics,
                    const SparseArray<Score> &score,
                    const SparseArray<Tag> &tags);
};
} // namespace rtype::server::systems

// check si tt le monde
// spawn enemis

// if tt le monde est mort envoyer gameover
// reset basics