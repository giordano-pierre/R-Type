/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MessageHandlerSys
*/

#include "systems/MessageHandlerSys.hpp"
#include "events/CreateEvent.hpp"
#include "events/DeleteEvent.hpp"
#include "events/RequestEvent.hpp"
#include <iostream>

namespace rtype::client {

Entity getEntityByID(const std::string &id, const SparseArray<Tag> &tags) {
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._id == id)
            return Entity(i);
    }
    return Entity(0);
}

void joinRoom(ECS &ecs, const ReceiveEvent &rec_event, Room &myRoom) {
    myRoom._idRoom = rec_event.payload["idr"].get<std::string>();

    myRoom._level = rec_event.payload["st"];
    if (rec_event.payload.contains("master"))
        myRoom._master = true;
    else
        myRoom._master = false;
    if (!myRoom._gameState) {
        ecs.post<DeleteEvent>({M_ROOM});
        ecs.post<DeleteEvent>({M_IN_ROOM});
        ecs.post<CreationEvent>({M_IN_ROOM});
    }
}

int countPlayer(ECS &ecs) {
    int cmpt = 0;
    const auto &players = ecs.get_components<Playable>();

    for (size_t i = 0; i < players.size(); ++i) {
        const auto &play = players[i];

        if (play)
            cmpt += 1;
    }
    return cmpt;
}

void createDrawable(ECS &ecs, Entity &entity, SFMLObjects &SFMLObj,
                    EntityType type) {
    switch (type) {
    case PLAYER:
        ecs.add_component<Drawable>(
            entity,
            {SFMLObj._myTextures.getTexture("assets/images/ship/red_ship.png"),
             {395, 250},
             {395, 250},
             1,
             1});
        break;
    case SHOT:
        ecs.add_component<Drawable>(entity,
                                    {SFMLObj._myTextures.getTexture(
                                         "assets/images/shot/purple_shot.png"),
                                     {251, 144},
                                     {251, 144},
                                     1,
                                     2});
        break;
    case ENEMY1:
        ecs.add_component<Drawable>(entity,
                                    {SFMLObj._myTextures.getTexture(
                                         "assets/images/ship/enemy_ship_1.png"),
                                     {2030, 1450},
                                     {290, 290},
                                     35,
                                     1});
        break;
    }
}

void createEntity(ECS &ecs, Entity &entity, const ReceiveEvent &rec_event,
                  SFMLObjects &SFMLObj) {
    if (rec_event.payload.contains("type") &&
        rec_event.payload.contains("id")) {
        ecs.add_component<Tag>(entity,
                               {rec_event.payload["type"].get<EntityType>(),
                                rec_event.payload["id"].get<std::string>()});
        createDrawable(ecs, entity, SFMLObj,
                       rec_event.payload["type"].get<EntityType>());
    }
    if (rec_event.payload.contains("hit"))
        ecs.add_component<Hitbox>(
            entity, {{rec_event.payload["hit"]["x"].get<float>(),
                      rec_event.payload["hit"]["y"].get<float>()}});
    if (rec_event.payload.contains("pos"))
        ecs.add_component<Position>(
            entity, {rec_event.payload["pos"]["x"].get<float>(),
                     rec_event.payload["pos"]["y"].get<float>()});
    if (rec_event.payload.contains("vel"))
        ecs.add_component<Velocity>(entity,
                                    {rec_event.payload["vel"]["x"].get<int>(),
                                     rec_event.payload["vel"]["y"].get<int>()});
    if (rec_event.payload.contains("name") &&
        rec_event.payload.contains("color"))
        ecs.add_component<PlayerData>(
            entity, {rec_event.payload["name"].get<std::string>(),
                     rec_event.payload["color"].get<std::string>()});
    if (rec_event.payload.contains("hp"))
        ecs.add_component<Health>(entity, {rec_event.payload["hp"].get<int>()});
    if (rec_event.payload.contains("sc"))
        ecs.add_component<Score>(entity, {rec_event.payload["sc"].get<int>()});
    ecs.add_component<LastUpdate>(entity, {1});
    ecs.add_component<Scene>(entity, {GAME});
}

bool entityExist(const ReceiveEvent &rec_event, const SparseArray<Tag> &tags) {
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag &&
            tag.value()._id == rec_event.payload["id"].get<std::string>())
            return true;
    }
    return false;
}

void createPlayer(ECS &ecs, const ReceiveEvent &rec_event, Room &myRoom,
                  SFMLObjects &SFMLObj, const SparseArray<Tag> &tags) {
    if (!entityExist(rec_event, tags)) {
        Entity player = ecs.spawn_entity();
        createEntity(ecs, player, rec_event, SFMLObj);
        std::cout << "PC " << countPlayer(ecs) + 1 << std::endl;
        ecs.add_component<Playable>(player, {countPlayer(ecs) + 1});
        if (myRoom._gameState)
            return;
        ecs.post<DeleteEvent>({M_IN_ROOM});
        ecs.post<DeleteEvent>({MENU});
        ecs.post<CreationEvent>({GAME});
        myRoom._gameState = true;
    }
}

void updateEntity(Entity &entity, const ReceiveEvent &rec_event,
                  SparseArray<Position> &positions,
                  SparseArray<Velocity> &velocities,
                  SparseArray<Health> &healths, SparseArray<Score> &scores,
                  SparseArray<LastUpdate> &lastups) {
    if (rec_event.payload.contains("pos") && entity < positions.size() &&
        positions[entity]) {
        positions[entity].value()._server = {
            rec_event.payload["pos"]["x"].get<float>(),
            rec_event.payload["pos"]["y"].get<float>()};
        positions[entity].value()._needUpdate = true;
    }
    if (rec_event.payload.contains("vel") && entity < velocities.size() &&
        velocities[entity]) {
        velocities[entity].value()._current = {
            rec_event.payload["vel"]["x"].get<int>(),
            rec_event.payload["vel"]["y"].get<int>()};
    }
    if (rec_event.payload.contains("hp") && entity < healths.size() &&
        healths[entity]) {
        healths[entity].value()._health = rec_event.payload["hp"].get<int>();
    }
    if (rec_event.payload.contains("sc") && entity < scores.size() &&
        scores[entity]) {
        scores[entity].value()._score = rec_event.payload["sc"].get<int>();
    }
    if (rec_event.payload.contains("lu") && entity < lastups.size() &&
        lastups[entity]) {
        lastups[entity].value()._lastUpdate =
            rec_event.payload["lu"].get<int>();
        if (lastups[0].value()._lastUpdate != rec_event.payload["lu"].get<int>()) {
            lastups[0].value()._lastUpdate = rec_event.payload["lu"].get<int>();
        }
    }
}

void killEntity(ECS &ecs, const ReceiveEvent &rec_event,
                const SparseArray<Tag> &tags) {
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag &&
            tag.value()._id == rec_event.payload["id"].get<std::string>()) {
            killMyEntity(ecs, ecs.entity_from_index(i));
        }
    }
}

void MessageHandlerSys::operator()(
    ECS &ecs, const ReceiveEvent &rec_event, SparseArray<Room> &rooms,
    SparseArray<SFMLObjects> &SFMLObjs, const SparseArray<Tag> &tags,
    SparseArray<Position> &positions, SparseArray<Velocity> &velocities,
    SparseArray<Health> &healths, SparseArray<Score> &scores,
    SparseArray<LastUpdate> &lastups) {
    auto &myRoom = rooms[0].value();
    auto &SFMLObj = SFMLObjs[0].value();

    std::cout << rec_event.action << std::endl;
    std::cout << rec_event.payload.dump() << std::endl;
    switch (rec_event.action) {
    case JOIN_ROOM: {
        joinRoom(ecs, rec_event, myRoom);
        break;
    }
    case SV_CREATE_PLAYER: {
        createPlayer(ecs, rec_event, myRoom, SFMLObj, tags);
        ecs.post<RequestEvent>({SV_CREATE_PLAYER, {{"idr", myRoom._idRoom}}});
        break;
    }
    case SV_GAME_OVER: {
        ecs.post<DeleteEvent>({GAME});
        ecs.post<CreationEvent>({M_IN_ROOM});
        ecs.post<CreationEvent>({MENU});
        myRoom._gameState = false;
        ecs.post<RequestEvent>({SV_GAME_OVER, {{"idr", myRoom._idRoom}}});
        break;
    }
    case SV_CREATE_ENTITY: {
        if (!entityExist(rec_event, tags)) {
            Entity entity = ecs.spawn_entity();
            createEntity(ecs, entity, rec_event, SFMLObj);
        }
        break;
    }
    case SV_UPDATE_ENTITY: {
        if (!entityExist(rec_event, tags)) {
            Entity entity = ecs.spawn_entity();
            createEntity(ecs, entity, rec_event, SFMLObj);
        } else {
            Entity entity =
                getEntityByID(rec_event.payload["id"].get<std::string>(), tags);
            updateEntity(entity, rec_event, positions, velocities, healths,
                         scores, lastups);
        }
        break;
    }
    case SV_KILL_ENTITY: {
        killEntity(ecs, rec_event, tags);
        break;
    }
    case GET_ROOM: {
        ecs.post<DeleteEvent>({M_PLAYER});
        ecs.post<DeleteEvent>({M_ROOM});
        ecs.post<CreationEvent>({M_ROOM, rec_event});
        break;
    }
    default:
        break;
    }
}

} // namespace rtype::client
