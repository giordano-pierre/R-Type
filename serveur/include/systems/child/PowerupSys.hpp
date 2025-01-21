/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PowerupSys.hpp
*/

#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "Events.hpp"
#include <random>

namespace rtype::server {
class PowerupSys {
  public:
    PowerupSys() = default;
    ~PowerupSys() = default;

    void spawnPowerup(ECS &ecs, float x, float y) {

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> probDis(0.0, 1.0);
        std::uniform_int_distribution<> typeDis(0, 1);

        if (probDis(gen) < 0.2) { // define the chance of appearance
            // if (1) { //define th/§e chance of appearance
            int powerupType = typeDis(gen);
            // int powerupType = 1;

            Entity powerup = ecs.spawn_entity();
            ecs.add_component<Position>(powerup, {x, y});
            ecs.add_component<Powerup>(powerup, {powerupType, 10});
            ecs.add_component<Tag>(powerup, {fetch_new_uuid(), POWERUP});
            ecs.add_component<HitBox>(powerup, HitBox(0.040, 0.060));
            ecs.add_component<Velocity>(powerup, Velocity(-1, 0));

            std::cout << "Pup spawned at (" << x << ", " << y
                      << ") Type: " << powerupType << " Duration: " << 10
                      << std::endl;
        }
    }

    void operator()(ECS &ecs, const PowerupEvent &event) {
        spawnPowerup(ecs, event._x, event._y);
    }
};
} // namespace rtype::server
