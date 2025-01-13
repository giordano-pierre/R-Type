/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ServerHandlerSystem.cpp
*/

#include "ServerHandlerSystem.hpp"
#include <iostream>

// void serverReady(ECS &ecs, const std::string &uuid) {
//     ecs.post<RequestEvent>({Protocol::GAME_START, {}, uuid});
// }

// void createEnemy(ECS &ecs, rtype::server::EnemyInfo enemy) {
//     Entity newPlayer = ecs.spawn_entity();
//     std::string uuid = fetch_new_uuid();

//     ecs.add_component<rtype::server::Position>(newPlayer,
//                                                {enemy.x_pos, enemy.y_pos});
//     ecs.add_component<rtype::server::Velocity>(
//         newPlayer, {enemy.x_velocity, enemy.y_velocity, true});
//     ecs.add_component<rtype::server::HitBox>(newPlayer,
//                                              {enemy.x_hitbox,
//                                              enemy.y_hitbox});
//     ecs.add_component<rtype::server::Health>(newPlayer, {});
//     ecs.add_component<rtype::server::Score>(newPlayer, {enemy.score});
//     ecs.add_component<rtype::server::Tag>(newPlayer,
//                                           {uuid, EntityType::ENEMY1});

//     ecs.post<RequestEvent>(
//         {Protocol::CREATE_ENTITY,
//          {{"id", uuid},
//           {"type", to_json(EntityType::ENEMY1)},
//           {"pos", {{"x", enemy.x_pos}, {"y", enemy.y_pos}}},
//           {"health", {enemy.health}},
//           {"velocity", {{"x", enemy.x_velocity}, {"y", enemy.y_velocity}}},
//           {"hitbox", {{"x", enemy.x_hitbox}, {"y", enemy.y_hitbox}}},
//           {"score", {enemy.score}}},
//          ""});
// }

// void gameOver(ECS &ecs) {

//     ecs.post<RequestEvent>({Protocol::GAME_OVER, {}, ""});
// }

// void updateEntity(ECS &ecs) {
//     auto &basic = ecs.get_components<rtype::server::Basics>()[0].value();

//     if (basic.nbPlayer != basic.minPlayer)
//         return;

//     auto tags = ecs.get_components<rtype::server::Tag>();
//     auto pos = ecs.get_components<rtype::server::Position>();
//     auto health = ecs.get_components<rtype::server::Health>();
//     auto score = ecs.get_components<rtype::server::Score>();
//     auto hitbox = ecs.get_components<rtype::server::HitBox>();
//     auto velocities = ecs.get_components<rtype::server::Velocity>();

//     for (size_t i = 0; i < tags.size(); i++) {
//         if (tags[i] && tags[i].value().type == EntityType::PLAYER) {
//             auto player = tags[i].value();
//             auto player_pos = pos[i].value();
//             auto player_health = health[i].value();
//             auto player_score = score[i].value();

//             ecs.post<RequestEvent>(
//                 {Protocol::UPDATE_ENTITY,
//                  {
//                      {"id", player.id},
//                      {"type", to_json(EntityType::PLAYER)},
//                      {"health", player_health.health},
//                      {"pos", {{"x", player_pos.x}, {"y", player_pos.y}}},
//                      {"score", player_score.score},
//                      {"hitbox", {{"x", 0.1}, {"y", 0.12}}},
//                  },
//                  ""});
//         }
//         if (tags[i] && tags[i].value().type == EntityType::ENEMY1) {
//             auto enemy = tags[i].value();
//             auto enemy_pos = pos[i].value();
//             auto enemy_health = health[i].value();
//             auto enemy_score = score[i].value();
//             auto enemy_box = hitbox[i].value();
//             auto enemy_vel = velocities[i].value();
//             ecs.post<RequestEvent>(
//                 {Protocol::UPDATE_ENTITY,
//                  {
//                      {"id", enemy.id},
//                      {"type", to_json(EntityType::ENEMY1)},
//                      {"health", enemy_health.health},
//                      {"pos", {{"x", enemy_pos.x}, {"y", enemy_pos.y}}},
//                      {"score", enemy_score.score},
//                      {"hitbox", {{"x", enemy_box.x}, {"y", enemy_box.y}}},
//                      {"velocity", {{"x", enemy_vel.x}, {"y", enemy_vel.y}}},
//                  },
//                  ""});
//         }
//         if (tags[i] && tags[i].value().type == EntityType::SHOT) {
//             auto shot = tags[i].value();
//             auto shot_pos = pos[i].value();
//             auto shot_box = hitbox[i].value();
//             auto shot_vel = velocities[i].value();
//             ecs.post<RequestEvent>(
//                 {Protocol::UPDATE_ENTITY,
//                  {
//                      {"id", shot.id},
//                      {"type", EntityType::SHOT},
//                      {"pos", {{"x", shot_pos.x}, {"y", shot_pos.y}}},
//                      {"velocity", {{"x", shot_vel.x}, {"y", shot_vel.y}}},
//                      {"hitbox", {{"x", shot_box.x}, {"y", shot_box.y}}},
//                  },
//                  ""});
//         }
//     }
// }

// void ServerHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event)
// {
//     // std::cout << "SERVER HANDLER" << std::endl;
//     // std::cout << "action : " << rec_event.action << std::endl;

//     switch (rec_event.action) {
//     case Protocol::NEW_CLIENT: {
//         ecs.post<RequestEvent>(
//             {Protocol::SEND_UUID, rec_event.payload, rec_event.sender_uuid});
//         break;
//     }
//     case Protocol::CLIENT_READY: {
//         Entity newPlayer = ecs.spawn_entity();
//         std::string uuid = fetch_new_uuid();

//         auto &basic = ecs.get_components<rtype::server::Basics>()[0].value();
//         if (basic.minPlayer == -1) {
//             basic.minPlayer = rec_event.payload["nb_player_max"];
//             basic.nbPlayerAlive = 0;
//         }
//         basic.nbPlayer += 1;
//         basic.nbPlayerAlive += 1;
//         if (basic.clientInGame.find(rec_event.sender_uuid) ==
//             basic.clientInGame.end())
//             basic.clientInGame.insert({rec_event.sender_uuid, false});

//         ecs.add_component<rtype::server::PlayerData>(
//             newPlayer, {rec_event.payload["name"]});
//         ecs.add_component<rtype::server::Position>(
//             newPlayer, {100, (basic.nbPlayer * 10) % 1000});
//         ecs.add_component<rtype::server::HitBox>(newPlayer, {0.1, 0.12});
//         ecs.add_component<rtype::server::Velocity>(newPlayer, {0, 0});
//         ecs.add_component<rtype::server::Tag>(newPlayer,
//                                               {uuid, EntityType::PLAYER});
//         ecs.add_component<rtype::server::Score>(newPlayer, {});
//         ecs.add_component<rtype::server::Health>(newPlayer, {});

//         ecs.post<RequestEvent>(
//             {Protocol::CREATE_PLAYER,
//              {
//                  {"id", uuid},
//                  {"type", to_json(EntityType::PLAYER)},
//                  {"pos", {{"x", 100}, {"y", (basic.nbPlayer * 10) % 1000}}},
//                  {"hitbox", {{"x", 0.1}, {"y", 0.12}}},
//              },
//              rec_event.sender_uuid});
//         break;
//     }
//     case Protocol::GAME_START: {
//         auto &basic = ecs.get_components<rtype::server::Basics>()[0].value();

//         auto it = basic.clientInGame.find(rec_event.sender_uuid);
//         if (it != basic.clientInGame.end()) {
//             it->second = true;
//         }
//         break;
//     }
// case Protocol::CLIENT_CREATE: {
//     std::string uuid = fetch_new_uuid();
//     Entity newPlayer = ecs.spawn_entity();
//     std::size_t id;

//     auto temp = ecs.get_components<rtype::server::Tag>();
//     for (size_t i = 0; i < temp.size(); i++) {
//         if (temp[i])
//             if (rec_event.payload["player_id"] == temp[i].value().id)
//             {
//                 id = i;
//             }
//     }
//     ecs.add_component<rtype::server::PlayerData>(
//         newPlayer, {"", id});
//     ecs.add_component<rtype::server::Position>(
//         newPlayer, {rec_event.payload["pos"]["x"],
//                     rec_event.payload["pos"]["y"]});
//     ecs.add_component<rtype::server::HitBox>(
//         newPlayer, {rec_event.payload["hitbox"]["x"],
//                     rec_event.payload["hitbox"]["y"]});
//     ecs.add_component<rtype::server::Tag>(newPlayer,
//                                           {uuid, EntityType::SHOT});
//     ecs.post<RequestEvent>({Protocol::CREATE_ENTITY,
//                             {
//                                 {"tmp_id",
// rec_event.payload["tmp_id"]},
//                                 {"id", uuid},
//                                 {"type", rec_event.payload["type"]},
//                                 {"pos", rec_event.payload["pos"]},
//                                 {"velocity", {{"x",
// rec_event.payload["velocity"]["x"]},{"y",
//                                 rec_event.payload["velocity"]["y"]}}},
//                                 {"hitbox", {{"x",
// rec_event.payload["hitbox"]["x"]},{"y",
//                                 rec_event.payload["hitbox"]["y"]}}},
//                             },
//                             ""});
//     break;
// }
// case Protocol::CLIENT_INPUT: {

//     auto input = rec_event.payload["type_event"];
//     std::size_t id;

//     auto temp = ecs.get_components<rtype::server::Tag>();
//     for (size_t i = 0; i < temp.size(); i++) {
//         if (temp[i])
//             if (rec_event.payload["id"] == temp[i].value().id) {
//                 id = i;
//             }
//     }
//     auto &opt_pos = ecs.get_components<rtype::server::Velocity>()[id];
//     if (!opt_pos)
//         break;

//     auto &vel = opt_pos.value();
//     if (input == "Up")
//         vel.y = -8;
//     if (input == "Down")
//         vel.y = 8;
//     if (input == "Right")
//         vel.x = 8;
//     if (input == "Left")
//         vel.x = -8;
//     if (input == "ReleasedX")
//         vel.x = 0;
//     if (input == "ReleasedY")
//         vel.y = 0;
//     break;
// }

//     case Protocol::CLIENT_DISCONNECT: {
//         std::size_t id;

//         auto &basic = ecs.get_components<rtype::server::Basics>()[0].value();
//         auto temp = ecs.get_components<rtype::server::Tag>();
//         for (size_t i = 0; i < temp.size(); i++) {
//             if (temp[i]) {
//                 if (!rec_event.payload.contains("id"))
//                     break;
//                 if (rec_event.payload["id"] == temp[i].value().id) {
//                     id = i;
//                     basic.clientInGame.erase(temp[i].value().id);
//                     Entity entity(id);
//                     ecs.kill_entity(entity);
//                 }
//             }
//         }

//         basic.nbPlayer -= 1;
//         basic.nbPlayerAlive -= 1;
//         if (basic.nbPlayer <= 0) {
//             basic.level = 0;
//             basic.nbPlayer = 0;
//             basic.minPlayer = -1;
//             basic.nbPlayerAlive = -1;
//             basic.gameState = false;
//             basic.clientInGame.clear();
//         }
//         break;
//     }
//     default:
//         break;
//     }
// }

void ServerHandlerSystem::operator()(ECS &ecs, const ReceiveEvent &rec_event) {
    switch (rec_event.action) {
    case Protocol::DISCONNECT: {
        std::cout << "Player Deconnexion!" << std::endl;
        ecs.post<RequestEvent>(
            {Protocol::DISCONNECT, {}, rec_event.sender_uuid});
        break;
    }
    default:
        return;
    }
}
