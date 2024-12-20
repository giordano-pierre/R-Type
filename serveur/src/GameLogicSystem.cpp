#include "GameLogicSystem.hpp"
#include "ServerHandlerSystem.hpp"

namespace rtype::server {
namespace systems {

void rtype::server::systems ::GameLogicSys::operator()(
    ECS &ecs, const rtype::server::TicEvent &, SparseArray<Basics> &basics,
    const SparseArray<Score> &scores) {

    if (basics[0].value().nbPlayer == basics[0].value().minPlayer) {
        serverReady(ecs);
        int totalScore = 0;
        for (size_t i = 0; i < scores.size(); ++i) {
            auto const score = scores[i];
            if (!score)
                continue;
            totalScore += score.value().score;
            if (totalScore < basics[0].value().minScore) {
                auto enemy_list = basics[0].value().enemies1;
                for (size_t i = 0; i < enemy_list.size(); ++i) {
                    createEnemy(ecs, enemy_list[i]);
                }
            }
        }
    }
    if (basics[0].value().nbPlayerAlive == 0) {
        gameOver(ecs);
        basics[0].value().level = 0;
        basics[0].value().nbPlayer = 0;
    }
}
} // namespace systems
} // namespace rtype::server