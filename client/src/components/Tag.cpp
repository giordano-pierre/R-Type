/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#include "components/Tag.hpp"

std::ostream &operator<<(std::ostream &out, const Rtype::Client::Tag &tag) {
    out << "id: " << tag._id << std::endl;
    switch (tag._type) {
    case Rtype::Client::WINDOW:
        out << "Window";
        break;
    case Rtype::Client::BACKGROUND:
        out << "Background";
        break;
    case Rtype::Client::PLAYER:
        out << "Player";
        break;
    case Rtype::Client::SHOT:
        out << "Shot";
        break;
    default:
        break;
    }
    return out;
}
