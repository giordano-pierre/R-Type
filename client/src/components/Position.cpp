/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include "components/Position.hpp"

auto operator<<(std::ostream &out, const Rtype::Client::Position &position) -> std::ostream &
{
    out << "old: x = " << position._old.x << ", y = " << position._old.y << std::endl;
    out << "current: x = " << position._current.x << ", y = " << position._current.y;
    return out;
}
