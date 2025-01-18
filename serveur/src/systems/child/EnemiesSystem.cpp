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


} // namespace systems
} // namespace rtype::server