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

// enum Protocol {
//     // Connection
//     CONNECT = 1,
//     NEW_CLIENT,
//     SEND_UUID,

//     // Events
//     CLIENT_READY,
//     GAME_START,
//     CLIENT_CREATE,
//     CREATE_ENTITY,
//     UPDATE_ENTITY,
//     CLIENT_INPUT,
//     CLIENT_DISCONNECT,
//     GAME_OVER,
//     CREATE_PLAYER,
// };

enum Protocol {
    // Connexion
    CONNECT, // -> Serveur ajoute le client -> le client ajoute son uuid (vide , uuid)
    DISCONNECT, // -> Server supprime le client de toutes ces variable (vide, OK)

    // Room Handler
            // (info_room = id, nb_max, nb_cur)
            // (info_player = id, color)
    // GET_ROOM, // -> Serveur envoi les rooms au client (vide, info_rooms)
    // CREATE_ROOM, // -> Serveur crée une nouvelle room avec le client pour chef (info_room, id_room)
    JOIN_ROOM, // -> Serveur ajoute le joueur à la room -> informe les autres clients (id room, info_player) ?? sécu

    // Stage Handler
            // (info_stage = nb, diff, lock)
    // GET_STAGE, // -> Serveur envoi les niveaux au client (vide, info_stages)
    // SELECT_STAGE, // -> Serveur selectionne le niveaux pour la partie -> informe les autres clients (id_stage, info_stage)

    // Game Handler
            // (info_players = id, hp, sc)
    LAUNCH_GAME, // -> le Serveur lance la partie du client et enlève la room de la liste en attente (id_room, vide)
    PAUSE_GAME, // -> Serveur met en pause la partie du client (id_room, vide)
    QUIT_GAME, // -> Serveur retire le joueur et en promut un nouveau chef (si necessaire) (id_room, vide)
    SV_GAME_OVER, // -> Server informe la fin de partie (info_players)

    // Event
    CL_MOVE, // -> Server fais bouger le client (direction id_player, vide)
    CL_SHOOT, // -> Server fais tirer le client (type id_player, id_player or vide)

    // Entity Handler
            // (info_entity = id, type, hit, pos, vel, [hp], [sc])
    SV_CREATE_PLAYER, // Client crée une entité jouable (id_player, OK)
    SV_CREATE_ENTITY, // Client crée l'entity demandé (info_entity)
    SV_UPDATE_ENTITY, // Client met à jour ou crée l'entity demandé (info_entity)
    SV_KILL_ENTITY, // Client kill l'entité (id_entity) sécu???
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
    OTHER
};

const std::unordered_map<EntityType, std::string> TypeToString{
    {EntityType::ENEMY1, "Enemy1"}, {EntityType::ENEMY2, "Enemy2"},
    {EntityType::ENEMY3, "Enemy3"}, {EntityType::ENEMY4, "Enemy4"},
    {EntityType::ENEMY5, "Enemy5"}, {EntityType::ENEMY6, "Enemy6"},
    {EntityType::BOSS1, "Boss1"},   {EntityType::BOSS2, "Boss2"},
    {EntityType::PLAYER, "Player"}, {EntityType::SHOT, "Shot"},
    {EntityType::OTHER, "Other"}};

const std::unordered_map<std::string, EntityType> StringToType{
    {"Enemy1", EntityType::ENEMY1}, {"Enemy2", EntityType::ENEMY2},
    {"Enemy3", EntityType::ENEMY3}, {"Enemy4", EntityType::ENEMY4},
    {"Enemy5", EntityType::ENEMY5}, {"Enemy6", EntityType::ENEMY6},
    {"Boss1", EntityType::BOSS1},   {"Boss2", EntityType::BOSS2},
    {"Player", EntityType::PLAYER}, {"Shot", EntityType::SHOT},
    {"Other", EntityType::OTHER}};

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
