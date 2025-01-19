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
class EnemiesSys {
  private:
    sol::state lua;
    std::string scriptsPath = "serveur/script/EnemiesComponant.lua";
    std::unordered_map<size_t, float> entityTimes;

    void initLua();
    void registerComponents();
    void loadBehaviors();
    void updateBehavior(Position &pos, Velocity &vel, EnemyAI &ai, float dt, rtype::server::Position &posPlayer);

  public:
    EnemiesSys();
    ~EnemiesSys() = default;

    void operator()(ECS &ecs, const rtype::server::TicEvent &tic,
                    SparseArray<Position> &positions,
                    const SparseArray<Tag> &tags, SparseArray<EnemyAI> &ais,
                    SparseArray<Velocity> &velocities);
};
} // namespace rtype::server

std::vector<RequestEvent> createSineEnemy(ECS& ecs,  rtype::server::EnemyInfo enemy);
RequestEvent createEnemyWithAI(ECS& ecs, rtype::server::EnemyInfo enemyInfo,
                       rtype::server::EnemyAI::BehaviorType behavior);
std::vector<RequestEvent> createVFormation(ECS& ecs, rtype::server::EnemyInfo enemy);
std::vector<RequestEvent> createCircle(ECS& ecs, rtype::server::EnemyInfo enemy);
std::vector<RequestEvent> createChase(ECS& ecs, rtype::server::EnemyInfo enemy);