/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** MainMessageHandlerSys
*/

#include "systems/parent/MainMessageHandlerSys.hpp"
#include "Events.hpp"
#include "events/RequestEvent.hpp"
#include <iostream>

namespace rtype::server {

void createPlayer(Child &child, const std::string &name,
                  const std::string &color, const std::string &uuid) {
    Entity player = child._ecs_child.spawn_entity();
    child._ecs_child.add_component<Client>(player, {uuid});
    child._ecs_child.add_component<Tag>(player, {fetch_new_uuid(), PLAYER});
    child._ecs_child.add_component<PlayerData>(player, {name, color});
}

void disconnect(ECS &ecs, const ReceiveEvent &rec_event,
                SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                SparseArray<Child> &children) {
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;

    for (size_t i = 0;
         i < rooms.size() && i < tags.size() && i < children.size(); ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];
        auto &child = children[i];

        if (!ro || !tag ||
            ro.value()._clients_uuid.find(rec_event.sender_uuid) ==
                ro.value()._clients_uuid.end())
            continue;
        ro.value()._clients_uuid.erase(
            ro.value()._clients_uuid.find(rec_event.sender_uuid));
        ro.value()._nbPlayer -= nbPlayer;
        child.value()._ecs_child.post<RemoveClient>({rec_event.sender_uuid});
        if (ro.value()._nbPlayer <= 0)
            ecs.kill_entity(ecs.entity_from_index(i));
        else {
            if (ro.value()._master == rec_event.sender_uuid) {
                ro.value()._master = ro.value()._clients_uuid.begin()->first;
                ecs.post<RequestEvent>({JOIN_ROOM,
                                        {{"master", true},
                                         {"id", tag.value()._id},
                                         {"name", ro.value()._name},
                                         {"slot", ro.value()._nbPlayer}},
                                        ro.value()._master});
            }
        }
    }
    std::cout << "Player Deconnexion!" << std::endl;
    ecs.post<RequestEvent>({Protocol::DISCONNECT, {}, rec_event.sender_uuid});
}

void joinRoom(ECS &ecs, const ReceiveEvent &rec_event, SparseArray<Room> &rooms,
              SparseArray<Tag> &tags, SparseArray<Child> &children) {
    Entity roomE = Entity(-1);
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;
    for (size_t i = 0; i < rooms.size(); ++i) {
        auto &ro = rooms[i];

        if (ro && ro.value()._name ==
                      rec_event.payload["room_name"].get<std::string>()) {
            roomE = Entity(i);
            break;
        }
    }
    if (roomE == -1) {
        roomE = ecs.spawn_entity();
        std::string idRoom = fetch_new_uuid();
        std::string nameRoom = rec_event.payload["room_name"];
        ecs.add_component<Tag>(roomE, {idRoom});
        ecs.add_component<Room>(roomE,
                                {nameRoom, rec_event.sender_uuid, nbPlayer});
        ecs.add_component<Stage>(roomE, {1});
        ecs.add_component<Child>(roomE, {ecs, idRoom});
    } else {
        if ((rooms[roomE].value()._nbPlayer += nbPlayer) > 8)
            return;
        rooms[roomE].value()._clients_uuid.insert(
            {rec_event.sender_uuid, WAITING});
        rooms[roomE].value()._nbPlayer += nbPlayer;
    }
    auto namesP = rec_event.payload["n_player"].get<std::vector<std::string>>();
    auto colorsP =
        rec_event.payload["c_player"].get<std::vector<std::string>>();
    for (int i = 0; i < nbPlayer; i++)
        createPlayer(children[roomE].value(), namesP[i], colorsP[i],
                     rec_event.sender_uuid);
    for (const auto &[uuid, _] : rooms[roomE].value()._clients_uuid) {
        if (uuid == rec_event.sender_uuid)
            ecs.post<RequestEvent>({JOIN_ROOM,
                                    {{"master", true},
                                     {"id", tags[roomE].value()._id},
                                     {"name", rooms[roomE].value()._name},
                                     {"slot", rooms[roomE].value()._nbPlayer}},
                                    uuid});
        if (uuid == rec_event.sender_uuid)
            ecs.post<RequestEvent>({JOIN_ROOM,
                                    {{"id", tags[roomE].value()._id},
                                     {"name", rooms[roomE].value()._name},
                                     {"slot", rooms[roomE].value()._nbPlayer}},
                                    uuid});
    }
    return;
}

void launchGame(ECS &ecs, const ReceiveEvent &rec_event,
                SparseArray<Room> &rooms, SparseArray<Tag> &tags) {
    for (size_t i = 0; i < rooms.size() && i < tags.size(); ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];

        if (!ro || !tag ||
            ro.value()._clients_uuid.find(rec_event.sender_uuid) ==
                ro.value()._clients_uuid.end())
            continue;
        for (const auto &[uuid, _] : ro.value()._clients_uuid) {
        }
    }
}

void MainMessageHandlerSys::operator()(ECS &ecs, const ReceiveEvent &rec_event,
                                       SparseArray<Room> &rooms,
                                       SparseArray<Tag> &tags,
                                       SparseArray<Child> &children) {
    switch (rec_event.action) {
    case DISCONNECT: {
        disconnect(ecs, rec_event, rooms, tags, children);
        return;
    }
    case JOIN_ROOM: {
        joinRoom(ecs, rec_event, rooms, tags, children);
        return;
    }
    case LAUNCH_GAME: {
        launchGame(ecs, rec_event, rooms, tags);
    }
    default:
        break;
    }

    for (size_t i = 0; i < rooms.size() && i < children.size(); ++i) {
        auto &ro = rooms[i];
        auto &child = children[i];

        if (ro && child &&
            ro.value()._clients_uuid.find(rec_event.sender_uuid) !=
                ro.value()._clients_uuid.end()) {
            child.value()._ecs_child.post<ReceiveEvent>(rec_event);
            return;
        }
    }
}

} // namespace rtype::server
