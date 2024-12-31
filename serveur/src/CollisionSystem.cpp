/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem.cpp
*/

#include "CollisionSystem.hpp"

namespace rtype::server::systems {

void CollisionSys::operator()(ECS &ecs, const rtype::server::TicEvent &,
                              const SparseArray<Position> &positions,
                              const SparseArray<HitBox> &hitboxes,
                              const SparseArray<Tag> &tags,
                              SparseArray<Health> &healths,
                              const SparseArray<PlayerData> &playersdata,
                              SparseArray<Score> &scores) {

    for (size_t i = 0;
         i < positions.size() && i < hitboxes.size() && i < tags.size(); ++i) {

        const auto &hitboxe1 = hitboxes[i];
        const auto &position1 = positions[i];
        const auto &tag1 = tags[i];

        if (!hitboxe1 || !position1 || !tag1)
            continue;

        float tempx1 = position1.value().x - hitboxe1.value().width / 2;
        float tempy1 = position1.value().y - hitboxe1.value().height / 2;

        for (size_t j = i + 1;
             j < positions.size() && j < hitboxes.size() && j < tags.size();
             ++j) {

            const auto &hitboxe2 = hitboxes[j];
            const auto &position2 = positions[j];
            const auto &tag2 = tags[j];

            if (!hitboxe2 || !position2 || !tag2)
                continue;

            float tempx2 = position2.value().x - hitboxe2.value().width / 2;
            float tempy2 = position2.value().y - hitboxe2.value().height / 2;

            if (tempx1 + hitboxe1.value().width < tempx2 ||
                tempx2 + hitboxe2.value().width < tempx1 ||
                tempy1 + hitboxe1.value().height < tempy2 ||
                tempy2 + hitboxe2.value().height < tempy1)
                continue;

            // if (tag1.value().type == PLAYER && tag2.value().type == ENEMY1) {
            //     if (i < healths.size() && healths[i]) {
            //         healths[i].value().health -= 20;
            //     }
            // }
            // if (tag2.value().type == PLAYER && tag1.value().type == ENEMY1) {
            //     if (j < healths.size() && healths[j]) {
            //         healths[j].value().health -= 20;
            //     }
            // }
            if (tag1.value().type == SHOT && tag2.value().type == ENEMY1) {
                ecs.kill_entity(Entity(j));
                if (i < playersdata.size() && playersdata[i]) {
                    const std::size_t idPlayer = playersdata[i].value().id;
                    const auto enemyScore = scores[j].value().score;
                    scores[idPlayer].value().score += enemyScore;
                }
            }
            if (tag1.value().type == ENEMY1 && tag2.value().type == SHOT) {
                ecs.kill_entity(Entity(i));

                if (j < playersdata.size() && playersdata[j]) {
                    const std::size_t idPlayer = playersdata[j].value().id;
                    const auto enemyScore = scores[i].value().score;
                    scores[idPlayer].value().score += enemyScore;
                }
            }
        }
    }
}

void CollisionSys::operator()(ECS &ecs, const rtype::server::TicEvent &,
                              SparseArray<Position> &positions,
                              const SparseArray<Tag> &tags,
                              const SparseArray<HitBox> &hitboxes) {
    for (size_t i = 0;
         i < positions.size() && i < tags.size() && i < hitboxes.size(); ++i) {

        const auto &hitboxe = hitboxes[i];
        const auto &tag = tags[i];
        auto &position = positions[i];

        if (!hitboxe || !position || !tag)
            continue;

        switch (tag.value().type) {
        case PLAYER:
            if ((position.value().x - hitboxe.value().width / 2) < 0)
                position.value().x = hitboxe.value().width / 2;
            if ((position.value().y - hitboxe.value().height / 2) < 0)
                position.value().y = hitboxe.value().height / 2;
            if ((position.value().y + hitboxe.value().height / 2) > 1080)
                position.value().y = 1080 - (hitboxe.value().height / 2);
            if ((position.value().x + hitboxe.value().width / 2) > 1920)
                position.value().x = 1920 - (hitboxe.value().width / 2);
            break;
        case ENEMY1:
            if ((position.value().x + hitboxe.value().width / 2) < 0) {
                position.value().x = position.value().initialX;
                position.value().y = position.value().initialY;
            }
            if ((position.value().y + hitboxe.value().height / 2) < 0) {
                position.value().x = position.value().initialX;
                position.value().y = position.value().initialY;
            }
            if ((position.value().y - hitboxe.value().height / 2) > 1080) {
                position.value().x = position.value().initialX;
                position.value().y = position.value().initialY;
            }
            break;
        case SHOT:
            if ((position.value().x + hitboxe.value().width / 2) < 0)
                ecs.kill_entity(Entity(i));
            if ((position.value().y + hitboxe.value().height / 2) < 0)
                ecs.kill_entity(Entity(i));
            if ((position.value().y - hitboxe.value().height / 2) > 1080)
                ecs.kill_entity(Entity(i));
            if ((position.value().x - hitboxe.value().width / 2) > 1920)
                ecs.kill_entity(Entity(i));
            break;
        default:
            break;
        }
    }
}

} // namespace rtype::server::systems
