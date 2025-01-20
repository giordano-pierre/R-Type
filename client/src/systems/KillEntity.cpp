/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** KillEntity
*/

#include "systems/KillEntity.hpp"
#include "clientTools.hpp"
#include <cmath>

namespace rtype::client {

void KillEntity::operator()(ECS &ecs, const TicEvent &,
                            SparseArray<LastUpdate> &lastUp) {
    int base = lastUp[0].value()._lastUpdate;

    for (size_t i = 0; i < lastUp.size(); ++i) {
        auto lu = lastUp[i];

        if (lu && abs(base - lu.value()._lastUpdate) > 2 &&
            abs(base + 10 - lu.value()._lastUpdate) > 2)
            killMyEntity(ecs, ecs.entity_from_index(i));
    }
}

} // namespace rtype::client
