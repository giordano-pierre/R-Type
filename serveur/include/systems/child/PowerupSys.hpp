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

namespace rtype::server {
class PowerupSys {
  public:
    PowerupSys() = default;
    ~PowerupSys() = default;

    void operator()(ECS &ecs, const PowerupEvent &event) {
        Entity powerup = ecs.spawn_entity();

        ecs.add_component<Position>(powerup, {event._x, event._y});
        ecs.add_component<Powerup>(powerup, {event._type, event._duration});
        ecs.add_component<Tag>(powerup, {fetch_new_uuid(), POWERUP});
        ecs.add_component<HitBox>(powerup, HitBox(0.115, 0.120));
        ecs.add_component<Velocity>(powerup, Velocity(-1, 0));

        std::cout << "pup at " << event._x << ", " << event._y
                  << " type :" << event._type
                  << " duration: " << event._duration << std::endl;
    }
};
} // namespace rtype::server
