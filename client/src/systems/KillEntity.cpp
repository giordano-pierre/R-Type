/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** KillEntity
*/

#include "systems/KillEntity.hpp"
#include "clientTools.hpp"
#include <cmath>
#include <iostream>

namespace rtype::client {

void KillEntity::operator()(ECS &ecs, const TicEvent &, SparseArray<LastUpdate> &lastUp) {
    int base = lastUp[0].value()._lastUpdate;
    std::cout << "Base: " << base << std::endl;

    for (size_t i = 0; i < lastUp.size(); ++i) {
        auto &lu = lastUp[i];

        if (lu && abs(base - lu.value()._lastUpdate) > 10 &&
            abs((base + 20) - lu.value()._lastUpdate) > 10) {
            std::cout << base << " MOIIIIIIIIIIIIIIIIIII " << std::endl;
            std::cout << lu.value()._lastUpdate << std::endl;
            killMyEntity(ecs, ecs.entity_from_index(i));
        }
    }
}

} // namespace rtype::client
