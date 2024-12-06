/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

#include "components/Hitbox.hpp"

auto operator<<(std::ostream &out, const Rtype::Client::Hitbox &hitbox) -> std::ostream &
{
    out << "Size: " << hitbox._coefSize.x * 100 << " %% of the width and ";
    out << hitbox._coefSize.y * 100 << " %% of height of the window.";
    return out;
}
