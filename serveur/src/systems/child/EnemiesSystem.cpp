/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemiesSystem.cpp
*/

#include "systems/child/EnemiesSystem.hpp"

namespace rtype::server {
namespace systems {
EnemiesSys::EnemiesSys() { initLua(); }

void EnemiesSys::initLua() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
    registerComponents();
    loadBehaviors();
}
void EnemiesSys::registerComponents() {
    lua.new_enum<EnemyAI::BehaviorType>(
        "BehaviorType", { {"SINUSOIDAL", EnemyAI::BehaviorType::SINUSOIDAL},
                         {"CIRCULAR", EnemyAI::BehaviorType::CIRCULAR},
                         {"CHASE", EnemyAI::BehaviorType::CHASE},
                         {"V_FORMATION", EnemyAI::BehaviorType::V_FORMATION},
                         {"BOSS", EnemyAI::BehaviorType::BOSS} });

    lua.new_usertype<EnemyAI>("EnemyAI", "behaviorType", &EnemyAI::behaviorType,
        "amplitude", &EnemyAI::amplitude, "frequency",
        &EnemyAI::frequency, "radius", &EnemyAI::radius,
        "speed", &EnemyAI::speed, "spacing",
        &EnemyAI::spacing, "index", &EnemyAI::index);

    lua.new_usertype<Position>("Position", "x", &Position::x, "y",
        &Position::y);

    lua.new_usertype<Velocity>("Velocity", "x", &Velocity::x, "y",
        &Velocity::y);
}

void EnemiesSys::loadBehaviors() {
    try {
        lua.script_file(scriptsPath);
    }
    catch (const sol::error& e) {
        std::cerr << "Erreur lors du chargement des comportements: " << e.what()
            << std::endl;
    }
}

void EnemiesSys::operator()(ECS& ecs, const rtype::server::TicEvent& tic,
    SparseArray<Position>& positions,
    const SparseArray<Tag>& tags,
    SparseArray<EnemyAI>& ais,
    SparseArray<Velocity>& velocities) {
    for (size_t i = 0; i < positions.size(); ++i) {
        if (!positions[i] || !tags[i] || !ais[i] || !velocities[i])
            continue;
        if ((*tags[i])._type != EntityType::ENEMY1)
            continue;
        auto& pos = *positions[i];
        auto& ai = *ais[i];
        auto& vel = *velocities[i];
        static timer::time_point<timer::steady_clock> lastTic = tic.time_stamp;
        float delta =
            std::chrono::duration<float>(tic.time_stamp - lastTic).count();
        lastTic = tic.time_stamp;
        updateBehavior(pos, vel, ai, delta);
    }
}

void EnemiesSys::updateBehavior(Position& pos, Velocity& vel, EnemyAI& ai,
    float dt) {
    switch (ai.behaviorType) {
    case EnemyAI::BehaviorType::SINUSOIDAL: {
        sol::function update = lua["SineMovement"]["update"];
        if (update.valid()) {
            sol::protected_function_result result =
                update(lua["SineMovement"], pos, vel, ai, dt);
            if (!result.valid()) {
                sol::error err = result;
                std::cerr << "Lua error: " << err.what() << std::endl;
            }
        }
        break;
    }
    case EnemyAI::BehaviorType::CIRCULAR: {
        sol::function update = lua["CircleMovement"]["update"];
        if (update.valid()) {
            update(pos, vel, ai, dt);
        }
        break;
    }
    case EnemyAI::BehaviorType::CHASE: {
        sol::function update = lua["PlayerChase"]["update"];
        if (update.valid()) {
            update(pos, vel, ai, dt);
        }
        break;
    }
    case EnemyAI::BehaviorType::V_FORMATION: {
        sol::function update = lua["VFormation"]["update"];
        if (update.valid()) {
            update(pos, vel, ai, dt);
        }
        break;
    }
    case EnemyAI::BehaviorType::BOSS: {
        sol::function update = lua["BossBehavior"]["update"];
        if (update.valid()) {
            update(pos, vel, ai, dt);
        }
        break;
    }
    }
}


} // namespace systems
} // namespace rtype::server