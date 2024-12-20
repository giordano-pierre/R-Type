/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLogicSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"

namespace rtype::server {
namespace systems {

class GameLogicSys {

  public:
    GameLogicSys() = default;
    ~GameLogicSys() = default;

    void operator()(ECS &ecs, const rtype::server::TicEvent &,
                    SparseArray<::rtype::server::Basics> &basics,
                    const SparseArray<::rtype::server::Score> &score);
};
} // namespace systems
} // namespace rtype::server

// check si tt le monde
// spawn enemis

// if tt le monde est mort envoyer gameover
// reset basics