/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#include "components/Tag.hpp"

std::ostream &operator<<(std::ostream &out, const rtype::client::Tag &tag) {
    out << "id: " << tag._id << std::endl;
    switch (tag._type) {
    case rtype::client::WINDOW:
        out << "Window";
        break;
    case rtype::client::BACKGROUND:
        out << "Background";
        break;
    case rtype::client::PLAYER:
        out << "Player";
        break;
    case rtype::client::SHOT:
        out << "Shot";
        break;
    default:
        break;
    }
    return out;
}
