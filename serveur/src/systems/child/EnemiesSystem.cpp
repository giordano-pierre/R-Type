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

} // namespace systems
} // namespace rtype::server