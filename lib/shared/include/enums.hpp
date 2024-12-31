/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** enums
*/
#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>

enum Protocol {
    // Connection
    CONNECT = 1,
    NEW_CLIENT,
    SEND_UUID,

    // Events
    CLIENT_READY,
    GAME_START,
    CLIENT_CREATE,
    CREATE_ENTITY,
    UPDATE_ENTITY,
    CLIENT_INPUT,
    CLIENT_DISCONNECT,
    GAME_OVER,
    CREATE_PLAYER,
};

enum EntityType {
    ENEMY1 = 1,
    ENEMY2,
    ENEMY3,
    ENEMY4,
    ENEMY5,
    ENEMY6,
    BOSS1,
    BOSS2,
    PLAYER,
    SHOT,
};

const std::unordered_map<EntityType, std::string> TypeToString{
    {EntityType::ENEMY1, "Enemy1"},
    {EntityType::ENEMY2, "Enemy2"},
    {EntityType::ENEMY3, "Enemy3"},
    {EntityType::ENEMY4, "Enemy4"},
    {EntityType::ENEMY5, "Enemy5"},
    {EntityType::ENEMY6, "Enemy6"},
    {EntityType::BOSS1, "Boss1"},
    {EntityType::BOSS2, "Boss2"},
    {EntityType::PLAYER, "Player"},
    {EntityType::SHOT, "Shot"}
};

const std::unordered_map<std::string, EntityType> StringToType{
    {"Enemy1", EntityType::ENEMY1},
    {"Enemy2", EntityType::ENEMY2},
    {"Enemy3", EntityType::ENEMY3},
    {"Enemy4", EntityType::ENEMY4},
    {"Enemy5", EntityType::ENEMY5},
    {"Enemy6", EntityType::ENEMY6},
    {"Boss1", EntityType::BOSS1},
    {"Boss2", EntityType::BOSS2},
    {"Player", EntityType::PLAYER},
    {"Shot", EntityType::SHOT}
};

inline nlohmann::json to_json(const EntityType &type) {
    return TypeToString.at(type);
}

inline EntityType from_json(const nlohmann::json &j) {
    return StringToType.at(j.get<std::string>());
}

inline std::string fetch_new_uuid() {
    boost::uuids::random_generator uuid_generator_;
    return boost::uuids::to_string(uuid_generator_());
}
