/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.cpp
*/

#include "systems/child/CollisionSystem.hpp"
#include <iostream>

namespace rtype::server {

size_t getShotOwner(ECS &ecs, const SparseArray<Tag> &tags,
                    const std::string &id) {
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._id == id) {
            return i;
        }
    }
    return -1;
}

void CollisionSys::operator()(ECS &ecs, const TicEvent &,
                              const SparseArray<Position> &positions,
                              const SparseArray<HitBox> &hitboxes,
                              const SparseArray<Tag> &tags,
                              SparseArray<Health> &healths,
                              const SparseArray<Owner> &owners,
                              SparseArray<Score> &scores) {
    for (size_t i = 0;
         i < positions.size() && i < hitboxes.size() && i < tags.size(); ++i) {

        const auto &box1 = hitboxes[i];
        const auto &pos1 = positions[i];
        const auto &tag1 = tags[i];

        if (!box1 || !pos1 || !tag1)
            continue;

        float tempX1 = pos1.value().x - box1.value().width / 2;
        float tempY1 = pos1.value().y - box1.value().height / 2;

        for (size_t j = i + 1;
             j < positions.size() && j < hitboxes.size() && j < tags.size();
             ++j) {

            const auto &box2 = hitboxes[j];
            const auto &pos2 = positions[j];
            const auto &tag2 = tags[j];

            if (!box2 || !pos2 || !tag2)
                continue;

            float tempX2 = pos2.value().x - box2.value().width / 2;
            float tempY2 = pos2.value().y - box2.value().height / 2;

            if (tempX1 > tempX2 + box2.value().width ||
                tempX1 + box1.value().width < tempX2 ||
                tempY1 > tempY2 + box2.value().height ||
                tempY1 + box1.value().height < tempY2)
                continue;
            if (tag1.value()._type == PLAYER && isEnemy(tag2.value()._type)) {
                ecs.add_component<Dead>(ecs.entity_from_index(j), {});
                if (i < healths.size() && healths[i]) {
                    healths[i].value()._health -= 10;
                }
            }
            if (tag2.value()._type == PLAYER && isEnemy(tag1.value()._type)) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
                if (j < healths.size() && healths[j]) {
                    healths[j].value()._health -= 10;
                }
            }
            if (tag1.value()._type == SHOT && isEnemy(tag2.value()._type)) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
                ecs.add_component<Dead>(ecs.entity_from_index(j), {});

                if (i < owners.size() && owners[i]) {
                    const std::size_t idPlayer =
                        getShotOwner(ecs, tags, owners[i].value()._id_owner);
                    const auto enemyScore = scores[j].value()._score;
                    scores[idPlayer].value()._score += enemyScore;
                }
            }
            if (isEnemy(tag1.value()._type) && tag2.value()._type == SHOT) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
                ecs.add_component<Dead>(ecs.entity_from_index(j), {});

                if (j < owners.size() && owners[j]) {
                    const std::size_t idPlayer =
                        getShotOwner(ecs, tags, owners[j].value()._id_owner);
                    const auto enemyScore = scores[i].value()._score;
                    scores[idPlayer].value()._score += enemyScore;
                }
            }
        }
    }
}

void CollisionSys::operator()(ECS &ecs, const TicEvent &,
                              SparseArray<Position> &positions,
                              const SparseArray<Tag> &tags,
                              const SparseArray<HitBox> &hitboxes) {
    for (size_t i = 0;
         i < positions.size() && i < tags.size() && i < hitboxes.size(); ++i) {

        const auto &box = hitboxes[i];
        const auto &tag = tags[i];
        auto &pos = positions[i];

        if (!box || !pos || !tag)
            continue;

        switch (tag.value()._type) {
        case OTHER:
            break;
        case PLAYER:
            if ((pos.value().x - box.value().width / 2) < 0)
                pos.value().x = box.value().width / 2;
            if ((pos.value().y - box.value().height / 2) < 0)
                pos.value().y = box.value().height / 2;
            if ((pos.value().y + box.value().height / 2) > 1080)
                pos.value().y = 1080 - (box.value().height / 2);
            if ((pos.value().x + box.value().width / 2) > 1920)
                pos.value().x = 1920 - (box.value().width / 2);
            break;
        case SHOT:
            if ((pos.value().x + box.value().width / 2) < 0)
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            if ((pos.value().y + box.value().height / 2) < 0)
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            if ((pos.value().y - box.value().height / 2) > 1080)
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            if ((pos.value().x - box.value().width / 2) > 1920)
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            break;
        default:
            if ((pos.value().x + box.value().width / 2) < 0) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            }
            if ((pos.value().y + box.value().height) < 0) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            }
            if ((pos.value().y - box.value().height) > 1080) {
                ecs.add_component<Dead>(ecs.entity_from_index(i), {});
            }
            break;
        }
    }
}

} // namespace rtype::server
