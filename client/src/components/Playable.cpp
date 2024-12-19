/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

#include "components/Playable.hpp"

auto operator<<(std::ostream &out,
                const rtype::client::Playable &player) -> std::ostream & {
    out << "is the Player " << player._id;
    return out;
}
