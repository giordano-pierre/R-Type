/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Powerup.hpp
*/
#pragma once

namespace rtype::client {

struct Powerup {
    Powerup( int type) : _type(type) {};
    ~Powerup() = default;
    // Powerup(const Powerup&) = default;
    // Powerup& operator=(const Powerup&) = default;

     int _type;
    // float _duration;
};
}