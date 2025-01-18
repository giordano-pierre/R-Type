/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemiesSystem.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include <sol/sol.hpp>
#include <string>

namespace rtype::server {
namespace systems {
class EnemiesSys {
  private:
    sol::state lua;
    std::string scriptsPath = "serveur/script/EnemiesComponant.lua";
    std::unordered_map<size_t, float> entityTimes;

    void initLua();
    void registerComponents();
    void loadBehaviors();
    void updateBehavior(Position &pos, Velocity &vel, EnemyAI &ai, float dt);


};
} // namespace systems
} // namespace rtype::server