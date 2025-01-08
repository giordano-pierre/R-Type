/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLogicSystem
*/
#include "GameLogicSystem.hpp"
#include "ServerHandlerSystem.hpp"
#include <iostream>

namespace rtype::server::systems {

void GameLogicSys::operator()(ECS &ecs, const TicEvent &,
                              SparseArray<Basics> &basics,
                              const SparseArray<Score> &scores,
                              const SparseArray<Tag> &tags) {

    if (basics[0].value().nbPlayer == basics[0].value().minPlayer) {
        // for (const auto &[key, value] : basics[0].value().clientInGame) {
            // if (!value)
                // serverReady(ecs, key);
        // }
        if (basics[0].value().gameState == false) {
            basics[0].value().gameState = true;
            int totalScore = 0;
            auto enemy_list = basics[0].value().enemies1;
            for (size_t i = 0; i < enemy_list.size(); ++i) {
                // createEnemy(ecs, enemy_list[i]);
            }
            // for (size_t i = 0; i < scores.size(); ++i) {
            //     auto const score = scores[i];
            //     if (!score)
            //         continue;
            //     totalScore += score.value().score;
            //     if (totalScore < basics[0].value().minScore) {
            //     }
            // }
        }
    }
    if (basics[0].value().nbPlayerAlive == 0) {
        // gameOver(ecs);
        basics[0].value().level = 0;
        basics[0].value().nbPlayer = 0;
        basics[0].value().minPlayer = -1;
        basics[0].value().nbPlayerAlive = -1;
        basics[0].value().gameState = false;
        basics[0].value().clientInGame.clear();
        for (size_t i = 1; i < tags.size(); ++i) {
            ecs.kill_entity(ecs.entity_from_index(i));
        }
    }
}
} // namespace rtype::server::systems
