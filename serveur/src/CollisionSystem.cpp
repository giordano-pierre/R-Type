/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.cpp
*/

#include "CollisionSystem.hpp"

namespace rtype {
    namespace systems {

        auto CollisionSys::operator()(ECS &ecs,
                            SparseArray<Position> &positions,
                            const SparseArray<HitBox> &hitboxes) -> bool
        {
            for (size_t i = 0; i < positions.size() && i < hitboxes.size(); ++i) {
                if (positions[i].has_value() && hitboxes[i].has_value()) {

                    float pX = positions[i].value().x;
                    float pY = positions[i].value().y;
                    float hX = hitboxes[i].value().x;
                    float hY = hitboxes[i].value().y;
                    float hW = hitboxes[i].value().width;
                    float hH = hitboxes[i].value().height;

                    if (pX >= hX && pX <= hX + hW && pY >= hY && pY <= hY + hH)
                            return true;
                    return false;
                }
            }
            return false;
        }

        auto CollisionSys::operator()(ECS &ecs,
                            SparseArray<Position> &positions) -> bool
        {
            for (size_t i = 0; i < positions.size(); ++i) {
                if (positions[i].has_value()) {

                    float pX = positions[i].value().x;
                    float pY = positions[i].value().y;

                    if (pX >= 1920 && pX <= 0 && pY >= 1080 && pY <= 0)
                            return true;
                    return false;
                }
            }
            return false;
        }
    }
}