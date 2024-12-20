/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** NetworkActions.hpp
*/

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>

enum NetworkActions {
    CONNECT = 1,
    ENVOI_SERV,
    ENVOI_CLIENT,
    NEW_CLIENT,
    SEND_UUID,
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
    PLAYER,
    ENEMY1,
    SHOT,
};

const std::unordered_map<EntityType, std::string> TypeToString{
    {EntityType::PLAYER, "Player"},
    {EntityType::ENEMY1, "Enemy1"},
    {EntityType::SHOT, "Shot"}};

const std::unordered_map<std::string, EntityType> StringToType{
    {"Player", EntityType::PLAYER},
    {"Enemy1", EntityType::ENEMY1},
    {"Shot", EntityType::SHOT}};

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
