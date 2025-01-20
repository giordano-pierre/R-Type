/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Tag
*/

#include "components/Tag.hpp"

std::ostream &operator<<(std::ostream &out, const rtype::client::Tag &tag) {
    out << "id: " << tag._id << std::endl;

    return out;
}
