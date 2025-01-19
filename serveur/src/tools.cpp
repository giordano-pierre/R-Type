/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** tools
*/

#include "tools.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "events/ReceiveEvent.hpp"
#include "events/RequestEvent.hpp"
#include <iostream>

namespace rtype::server {

void removeAll(ECS &ecs) {
    const auto &tags = ecs.get_components<Tag>();

    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._type != OTHER) {
            std::cout << "B KILL" << std::endl;
            ecs.kill_entity(ecs.entity_from_index(i));
            std::cout << "A KILL" << std::endl;
        }
    }
}

bool isEnemy(const EntityType &obj) {
    if (obj >= ENEMY1 && obj <= BOSS2)
        return true;
    return false;
}

int ennemyError(const nlohmann::json &item) {
    int value = 0;

    if (!item.contains("type")) {
        std::cerr << "Ennemy: type is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("spawn_time")) {
        std::cerr << "Ennemy: spawn_time is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("hp")) {
        std::cerr << "Ennemy: hp is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("score")) {
        std::cerr << "Ennemy: score is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("position")) {
        std::cerr << "Ennemy: position is missing!" << std::endl;
        value = 1;
    }
    if (!item["position"].contains("x")) {
        std::cerr << "Ennemy: position 'x' is missing!" << std::endl;
        value = 1;
    }
    if (!item["position"].contains("y")) {
        std::cerr << "Ennemy: position 'y' is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("velocity")) {
        std::cerr << "Ennemy: velocity is missing!" << std::endl;
        value = 1;
    }
    if (!item["velocity"].contains("x")) {
        std::cerr << "Ennemy: velocity 'x' is missing!" << std::endl;
        value = 1;
    }
    if (!item["velocity"].contains("y")) {
        std::cerr << "Ennemy: velocity 'y' is missing!" << std::endl;
        value = 1;
    }
    if (!item.contains("hitbox")) {
        std::cerr << "Ennemy: hitbox is missing!" << std::endl;
        value = 1;
    }
    if (!item["hitbox"].contains("x")) {
        std::cerr << "Ennemy: hitbox 'x' is missing!" << std::endl;
        value = 1;
    }
    if (!item["hitbox"].contains("y")) {
        std::cerr << "Ennemy: hitbox 'y' is missing!" << std::endl;
        value = 1;
    }
    return value;
}

EnemyInfo extractEnnemy(const nlohmann::json &item) {
    EnemyInfo ennemy;

    ennemy.type = item["type"].get<EntityType>();
    ennemy.health = item["hp"].get<int>();
    ennemy.score = item["score"].get<int>();
    ennemy.spawn_tic = item["spawn_time"].get<int>();
    ennemy.x_pos = item["position"]["x"].get<float>();
    ennemy.y_pos = item["position"]["y"].get<float>();
    ennemy.x_hitbox = item["hitbox"]["x"].get<float>();
    ennemy.y_hitbox = item["hitbox"]["y"].get<float>();
    ennemy.x_velocity = item["velocity"]["x"].get<int>();
    ennemy.y_velocity = item["velocity"]["y"].get<int>();
    return ennemy;
}

void loadLevel(Stage &stage)
{
    stage._enemies.clear();
    if (!stage._json.contains("enemies")) {
        std::cerr << "no ennemies in level!" << std::endl;
        return;
    }
    if (!stage._json["enemies"].is_array()) {
        std::cerr << "The ennemy list isn't a array!" << std::endl;
        return;
    }
    for (const auto &item : stage._json["enemies"]) {
        if (ennemyError(item))
            break;
        stage._enemies.push_back(extractEnnemy(item));
    }
}

} // namespace rtype::server
