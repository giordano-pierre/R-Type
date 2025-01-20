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

Entity getEntityByID(const std::string &id, const SparseArray<Tag> &tags) {
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &tag = tags[i];

        if (tag && tag.value()._id == id)
            return Entity(i);
    }
    return Entity(0);
}

void movePlayer(const ReceiveEvent &rec_event, const SparseArray<Tag> &tags,
                SparseArray<Velocity> &velocities) {
    auto input = rec_event.payload["e_type"].get<std::string>();
    auto idp = rec_event.payload["idp"].get<std::string>();

    for (size_t i = 0; i < tags.size() && i < velocities.size(); ++i) {
        const auto &tag = tags[i];
        auto &vel = velocities[i];

        if (tag && vel && tag.value()._id == idp) {
            if (input == "up")
                vel.value().y = -8;
            if (input == "down")
                vel.value().y = 8;
            if (input == "right")
                vel.value().x = 8;
            if (input == "left")
                vel.value().x = -8;
            if (input == "releasedX")
                vel.value().x = 0;
            if (input == "releasedY")
                vel.value().y = 0;
        }
    }
}

int countPlayer(
    const std::map<std::string, std::pair<PlayerInfo, int>> &clients) {
    int cmpt = 0;
    for (const auto &[_, infos] : clients) {
        cmpt += infos.second;
    }
    return cmpt;
}

void createPlayers(
    Child &child,
    const std::map<std::string, std::pair<PlayerInfo, int>> &clients) {
    for (const auto &[uuid, infos] : clients) {
        for (int i = 0; i < infos.second; i++) {
            Entity player = child._ecs_child.spawn_entity();
            child._ecs_child.add_component<Client>(player, {uuid});
            child._ecs_child.add_component<Tag>(player,
                                                {fetch_new_uuid(), PLAYER});
            child._ecs_child.add_component<PlayerData>(
                player, {
                            infos.first._name[i],
                            infos.first._color[i],
                        });
            std::cout << "Player " << infos.first._name[i] << " "
                      << infos.first._color[i] << " is created." << std::endl;
        }
    }
}

void disconnect(ECS &ecs, const ReceiveEvent &rec_event,
                SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                SparseArray<Child> &children,
                const SparseArray<Stage> &stages) {
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;

    for (size_t i = 0; i < rooms.size() && i < tags.size() &&
                       i < children.size() && i < stages.size();
         ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];
        auto &child = children[i];
        const auto &st = stages[i];

        if (!ro || !tag || !child || !st ||
            ro.value()._clients_uuid.find(rec_event.sender_uuid) ==
                ro.value()._clients_uuid.end())
            continue;
        ro.value()._clients_uuid.erase(
            ro.value()._clients_uuid.find(rec_event.sender_uuid));
        child.value()._ecs_child.post<RemoveClient>({rec_event.sender_uuid});
        for (const auto &[uuid, _] : ro.value()._clients_uuid)
            std::cout << uuid << std::endl;
        if (ro.value()._clients_uuid.empty()) {
            ecs.kill_entity(ecs.entity_from_index(i));
            std::cout << "Destroy Room !!!" << std::endl;
        } else {
            if (ro.value()._master == rec_event.sender_uuid) {
                ro.value()._master = ro.value()._clients_uuid.begin()->first;
                ecs.post<RequestEvent>(
                    {JOIN_ROOM,
                     {{"master", true},
                      {"diff", ro.value()._diff},
                      {"idr", tag.value()._id},
                      {"r_name", ro.value()._name},
                      {"st", st.value()._mapFile},
                      {"nbp", countPlayer(ro.value()._clients_uuid)}},
                     ro.value()._master});
            }
        }
    }
    // std::cout << "Player Deconnexion!" << std::endl;
    // ecs.post<RequestEvent>({Protocol::DISCONNECT, {},
    // rec_event.sender_uuid});
}

int countRoom(const SparseArray<Room> &rooms) {
    int cmpt = 0;

    for (size_t i = 0; i < rooms.size(); ++i) {
        const auto &ro = rooms[i];

        if (ro)
            cmpt += 1;
    }
    return cmpt;
}

void createRoom(ECS &ecs, const ReceiveEvent &rec_event,
                SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                SparseArray<Child> &children,
                const SparseArray<Stage> &stages) {
    std::cout << rec_event.payload.dump() << std::endl;
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;
    if (countRoom(rooms) >= 10)
        return;
    Entity roomE = ecs.spawn_entity();
    std::string idRoom = fetch_new_uuid();
    std::string nameRoom = rec_event.payload["r_name"];
    ecs.add_component<Tag>(roomE, {idRoom});
    ecs.add_component<Room>(roomE, {nameRoom, rec_event.sender_uuid, nbPlayer,
                                    rec_event.payload["diff"].get<int>()});
    ecs.add_component<Stage>(roomE,
                             {rec_event.payload["st"].get<std::string>()});
    ecs.add_component<Child>(roomE, {});
    auto &tmp = ecs.get_components<Child>();
    initSubECS(tmp[roomE].value()._ecs_child);
    loadSubSystem(tmp[roomE].value());
    std::cout << "Room " << nameRoom << " created." << std::endl;
    auto namesP = rec_event.payload["p_name"].get<std::vector<std::string>>();
    auto colorsP = rec_event.payload["p_color"].get<std::vector<std::string>>();
    rooms[roomE].value()._clients_uuid.insert(
        {rec_event.sender_uuid, {{namesP, colorsP, WAITING}, nbPlayer}});
    ecs.post<RequestEvent>(
        {JOIN_ROOM,
         {{"master", true},
          {"diff", rooms[roomE].value()._diff},
          {"idr", tags[roomE].value()._id},
          {"r_name", rooms[roomE].value()._name},
          {"st", stages[roomE].value()._mapFile},
          {"nbp", countPlayer(rooms[roomE].value()._clients_uuid)}},
         rec_event.sender_uuid});
}

void updateRoom(ECS &ecs, const ReceiveEvent &rec_event,
                SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                SparseArray<Child> &children,
                const SparseArray<Stage> &stages) {
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;

    for (size_t i = 0; i < tags.size() && i < rooms.size() &&
                       i < children.size() && i < stages.size();
         ++i) {
        auto &tag = tags[i];
        auto &ro = rooms[i];
        auto &child = children[i];
        auto &st = stages[i];

        if (tag && ro && child && st &&
            tag.value()._id == rec_event.payload["idr"].get<std::string>()) {
            ro.value()._name = rec_event.payload["r_name"].get<std::string>();
            ro.value()._diff = rec_event.payload["diff"].get<int>();
            ecs.emplace_component<Stage>(
                Entity(i), rec_event.payload["st"].get<std::string>());
            for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                if (uuid == ro.value()._master) {
                    ecs.post<RequestEvent>(
                        {JOIN_ROOM,
                         {{"master", true},
                          {"diff", ro.value()._diff},
                          {"idr", tag.value()._id},
                          {"r_name", ro.value()._name},
                          {"st", st.value()._mapFile},
                          {"nbp", countPlayer(ro.value()._clients_uuid)}},
                         uuid});
                } else {
                    ecs.post<RequestEvent>(
                        {JOIN_ROOM,
                         {{"diff", ro.value()._diff},
                          {"idr", tag.value()._id},
                          {"r_name", ro.value()._name},
                          {"st", st.value()._mapFile},
                          {"nbp", countPlayer(ro.value()._clients_uuid)}},
                         uuid});
                }
            }
        }
    }
}

void joinRoom(ECS &ecs, const ReceiveEvent &rec_event, SparseArray<Room> &rooms,
              SparseArray<Tag> &tags, SparseArray<Child> &children,
              const SparseArray<Stage> &stages) {
    // Entity roomE = Entity(-1);
    int nbPlayer = (rec_event.payload.contains("nbp"))
                       ? rec_event.payload["nbp"].get<int>()
                       : 1;
    for (size_t i = 0; i < tags.size() && i < rooms.size() &&
                       i < children.size() && i < stages.size();
         ++i) {
        auto &tag = tags[i];
        auto &ro = rooms[i];
        auto &child = children[i];
        const auto &st = stages[i];

        if (tag && ro && child && st &&
            tag.value()._id == rec_event.payload["idr"].get<std::string>()) {
            if ((countPlayer(ro.value()._clients_uuid) + nbPlayer) > 8 ||
                ro.value()._clients_uuid.find(rec_event.sender_uuid) !=
                    ro.value()._clients_uuid.end() ||
                ro.value()._state != WAITING)
                return;
            std::cout << "Player add." << std::endl;
            auto namesP =
                rec_event.payload["p_name"].get<std::vector<std::string>>();
            auto colorsP =
                rec_event.payload["p_color"].get<std::vector<std::string>>();
            ro.value()._clients_uuid.insert(
                {rec_event.sender_uuid,
                 {{namesP, colorsP, WAITING}, nbPlayer}});
            // for (int i = 0; i < nbPlayer; i++)
            //     createPlayer(child.value(), namesP[i], colorsP[i],
            //     rec_event.sender_uuid);
            for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                if (uuid == ro.value()._master)
                    ecs.post<RequestEvent>(
                        {JOIN_ROOM,
                         {{"master", true},
                          {"diff", ro.value()._diff},
                          {"idr", tag.value()._id},
                          {"r_name", ro.value()._name},
                          {"st", st.value()._mapFile},
                          {"nbp", countPlayer(ro.value()._clients_uuid)}},
                         uuid});
                else
                    ecs.post<RequestEvent>(
                        {JOIN_ROOM,
                         {{"idr", tag.value()._id},
                          {"diff", ro.value()._diff},
                          {"r_name", ro.value()._name},
                          {"st", st.value()._mapFile},
                          {"nbp", countPlayer(ro.value()._clients_uuid)}},
                         uuid});
            }
            return;
        }
    }
    // }
    // // if (roomE == -1) {
    // //     roomE = ecs.spawn_entity();
    // //     std::string idRoom = fetch_new_uuid();
    // //     std::string nameRoom = rec_event.payload["r_name"];
    // //     ecs.add_component<Tag>(roomE, {idRoom});
    // //     ecs.add_component<Room>(roomE,
    // //                             {nameRoom, rec_event.sender_uuid,
    // nbPlayer});
    // //     ecs.add_component<Stage>(roomE, {utils._levels.getOneLevel(1)});
    // //     ecs.add_component<Child>(roomE, {});
    // //     auto &tmp = ecs.get_components<Child>();
    // //     initSubECS(tmp[roomE].value()._ecs_child);
    // //     loadSubSystem(tmp[roomE].value());
    // //     std::cout << "Room " << nameRoom << " created." << std::endl;
    // // } else {

    // }
    // auto namesP =
    // rec_event.payload["p_name"].get<std::vector<std::string>>(); auto colorsP
    // = rec_event.payload["p_color"].get<std::vector<std::string>>(); for (int
    // i = 0; i < nbPlayer; i++)
    //     createPlayer(children[roomE].value(), namesP[i], colorsP[i],
    //                  rec_event.sender_uuid);
    // for (const auto &[uuid, _] : rooms[roomE].value()._clients_uuid) {
    //     if (uuid == rooms[roomE].value()._master)
    //         ecs.post<RequestEvent>(
    //             {JOIN_ROOM,
    //              {{"master", true},
    //               {"idr", tags[roomE].value()._id},
    //               {"r_name", rooms[roomE].value()._name},
    //               {"nbp", countPlayer(rooms[roomE].value()._clients_uuid)}},
    //              uuid});
    //     else
    //         ecs.post<RequestEvent>(
    //             {JOIN_ROOM,
    //              {{"idr", tags[roomE].value()._id},
    //               {"r_name", rooms[roomE].value()._name},
    //               {"nbp", countPlayer(rooms[roomE].value()._clients_uuid)}},
    //              uuid});
    // }
    // return;
}

void launchGame(ECS &ecs, const ReceiveEvent &rec_event,
                const SparseArray<Room> &rooms, const SparseArray<Tag> &tags,
                SparseArray<Child> &children) {
    std::string idRoom = rec_event.payload["idr"];

    for (size_t i = 0;
         i < rooms.size() && i < tags.size() && i < children.size(); ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];
        auto &child = children[i];

        if (ro && tag && child && tag.value()._id == idRoom) {
            std::cout << "Launch " << idRoom << " game." << std::endl;
            createPlayers(child.value(), ro.value()._clients_uuid);
            float space = 1080 / (countPlayer(ro.value()._clients_uuid) + 1);
            float posY = 0;
            const auto subTags = child.value()._ecs_child.get_components<Tag>();
            const auto subPlayer =
                child.value()._ecs_child.get_components<PlayerData>();
            const auto subClients =
                child.value()._ecs_child.get_components<Client>();
            for (size_t j = 0; j < subTags.size() && j < subPlayer.size() &&
                               j < subClients.size();
                 ++j) {
                const auto &subTag = subTags[j];
                const auto &subPlay = subPlayer[j];
                const auto &subCl = subClients[j];

                if (subPlay && subTag && subCl) {
                    posY += space;
                    Entity tmpPlayer =
                        child.value()._ecs_child.entity_from_index(j);
                    child.value()._ecs_child.add_component<HitBox>(tmpPlayer,
                                                                   {0.1, 0.12});
                    child.value()._ecs_child.add_component<Velocity>(tmpPlayer,
                                                                     {0, 0});
                    child.value()._ecs_child.add_component<Health>(tmpPlayer,
                                                                   {});
                    child.value()._ecs_child.add_component<Score>(tmpPlayer,
                                                                  {0});
                    child.value()._ecs_child.add_component<Position>(
                        tmpPlayer, {100, posY});
                    std::cout << "SEND CREATE PLAYER" << std::endl;
                    RequestEvent req = {SV_CREATE_PLAYER,
                                        {{"id", subTag.value()._id},
                                         {"type", PLAYER},
                                         {"name", subPlay.value()._name},
                                         {"color", subPlay.value()._color},
                                         {"hit", {{"x", 0.1}, {"y", 0.12}}},
                                         {"pos", {{"x", 100}, {"y", posY}}},
                                         {"vel", {{"x", 0}, {"y", 0}}},
                                         {"hp", 10},
                                         {"sc", 0}},
                                        subCl.value()._uuid};
                    ecs.post<RequestEvent>(req);
                    // ecs.post<CheckEvent>({LAUNCH_GAME, tag.value()._id,
                    // req});
                }
            }
        }
    }
}

bool allPlayerReady(
    const std::map<std::string, std::pair<PlayerInfo, int>> &client_uuid) {
    for (const auto &[_, infos] : client_uuid) {
        if (infos.first._state != IN_GAME)
            return false;
    }
    return true;
}

void playerIsCreated(ECS &ecs, const ReceiveEvent &rec_event,
                     SparseArray<Room> &rooms, SparseArray<Tag> &tags,
                     SparseArray<Child> &children, SparseArray<Stage> &stages) {
    std::string idRoom = rec_event.payload["idr"];

    for (size_t i = 0; i < rooms.size() && i < tags.size() &&
                       i < children.size() && i < stages.size();
         ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];
        auto &child = children[i];
        auto &st = stages[i];

        if (ro && tag && child && st && tag.value()._id == idRoom) {
            auto client_it =
                ro.value()._clients_uuid.find(rec_event.sender_uuid);
            if (client_it == ro.value()._clients_uuid.end())
                return;
            client_it->second.first._state = IN_GAME;
            if (allPlayerReady(ro.value()._clients_uuid)) {
                ro.value()._state = IN_GAME;
                loadSubGameSystem(child.value());
                loadLevel(st.value());
            }
        }
    }
}

void playerShoot(ECS &ecs, const ReceiveEvent &rec_event,
                 const SparseArray<Room> &rooms, const SparseArray<Tag> &tags,
                 SparseArray<Child> &children) {
    for (size_t i = 0;
         i < rooms.size() && i < tags.size() && i < children.size(); ++i) {
        const auto &ro = rooms[i];
        const auto &tag = tags[i];
        auto &child = children[i];

        if (ro && tag && child) {
            if (ro.value()._clients_uuid.find(rec_event.sender_uuid) ==
                ro.value()._clients_uuid.end())
                return;
            auto &subTags = child.value()._ecs_child.get_components<Tag>();
            auto &subPosistions =
                child.value()._ecs_child.get_components<Position>();
            auto &subHitboxs =
                child.value()._ecs_child.get_components<HitBox>();
            Entity player = getEntityByID(rec_event.payload["idp"], subTags);
            std::string newId = fetch_new_uuid();
            nlohmann::json tmp = {
                {"id", newId},
                {"type", EntityType::SHOT},
                {"idp", rec_event.payload["idp"]},
                {"pos",
                 {
                     {"x", subPosistions[player].value().x +
                               (subHitboxs[player].value().x / 2)},
                     {"y", subPosistions[player].value().y},
                 }},
                {"vel",
                 {
                     {"x", 15},
                     {"y", 0},
                 }},
                {"hit",
                 {
                     {"x", 0.07},
                     {"y", 0.05},
                 }},
            };
            Entity newShot = child.value()._ecs_child.spawn_entity();
            child.value()._ecs_child.add_component<Tag>(newShot, {newId, SHOT});
            child.value()._ecs_child.add_component<Owner>(
                newShot, {rec_event.payload["idp"]});
            child.value()._ecs_child.add_component<Position>(
                newShot, {subPosistions[player].value().x +
                              (subHitboxs[player].value().x / 2),
                          subPosistions[player].value().y});
            child.value()._ecs_child.add_component<Velocity>(newShot, {15, 0});
            child.value()._ecs_child.add_component<HitBox>(newShot,
                                                           {0.07, 0.05});
            for (const auto &[uuid, _] : ro.value()._clients_uuid) {
                ecs.post<RequestEvent>({SV_CREATE_ENTITY, tmp, uuid});
            }
        }
    }
}

void gameOver(ECS &ecs, const ReceiveEvent rec_event, SparseArray<Room> &rooms,
              const SparseArray<Tag> &tags) {
    std::string idRoom = rec_event.payload["idr"];

    for (size_t i = 0; i < rooms.size() && i < tags.size(); ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];

        if (ro && tag && tag.value()._id == idRoom) {
            auto client_it =
                ro.value()._clients_uuid.find(rec_event.sender_uuid);
            if (client_it == ro.value()._clients_uuid.end())
                return;
            client_it->second.first._state = WAITING;
        }
    }
}

void getRoom(ECS &ecs, const ReceiveEvent &rec_event, SparseArray<Room> &rooms,
             SparseArray<Tag> &tags, SparseArray<Stage> &stages) {
    nlohmann::json r_name = nlohmann::json::array();
    nlohmann::json r_nbp = nlohmann::json::array();
    nlohmann::json r_id = nlohmann::json::array();
    nlohmann::json r_stage = nlohmann::json::array();

    for (size_t i = 0; i < rooms.size() && i < tags.size() && i < stages.size();
         ++i) {
        auto &ro = rooms[i];
        auto &tag = tags[i];
        auto &st = stages[i];

        if (ro && tag && st && ro.value()._state == WAITING) {
            r_name.push_back(ro.value()._name);
            r_id.push_back(tag.value()._id);
            r_nbp.push_back(countPlayer(ro.value()._clients_uuid));
            if (st.value()._json.contains("stage") &&
                st.value()._json["stage"].contains("name"))
                r_stage.push_back(st.value()._json["stage"]["name"]);
            else
                r_stage.push_back("");
        }
    }
    ecs.post<RequestEvent>({GET_ROOM,
                            {{"idr", r_id},
                             {"r_name", r_name},
                             {"r_nbp", r_nbp},
                             {"r_st", r_stage}},
                            rec_event.sender_uuid});
}

void getStage(ECS &ecs, const ReceiveEvent &rec_event, Utils &util) {
    nlohmann::json l_name = nlohmann::json::array();
    nlohmann::json l_file = nlohmann::json::array();

    for (const auto &[_, stage] : util._levels.getLevels()) {
        l_file.push_back(stage);
        std::ifstream f(stage);
        auto tmp_name = nlohmann::json::parse(f);
        if (tmp_name.contains("stage") && tmp_name["stage"].contains("name"))
            l_name.push_back(tmp_name["stage"]["name"]);
        else
            l_name.push_back("");
    }

    ecs.post<RequestEvent>({GET_STAGE,
                            {{"l_name", l_name}, {"l_file", l_file}},
                            rec_event.sender_uuid});
}

void MainMessageHandlerSys::operator()(ECS &ecs, const ReceiveEvent &rec_event,
                                       SparseArray<Utils> &utils,
                                       SparseArray<Room> &rooms,
                                       SparseArray<Tag> &tags,
                                       SparseArray<Stage> &stages,
                                       SparseArray<Child> &children) {
    auto &util = utils[0].value();

    std::cout << rec_event.action << std::endl;
    std::cout << rec_event.payload.dump() << std::endl;
    switch (rec_event.action) {
    case DISCONNECT: {
        disconnect(ecs, rec_event, rooms, tags, children, stages);
        std::cout << "Player Deconnexion!" << std::endl;
        ecs.post<RequestEvent>(
            {Protocol::DISCONNECT, {}, rec_event.sender_uuid});
        return;
    }
    case QUIT_ROOM: {
        disconnect(ecs, rec_event, rooms, tags, children, stages);
        std::cout << "Player quit Room!" << std::endl;
        ecs.post<RequestEvent>(
            {Protocol::QUIT_ROOM, {}, rec_event.sender_uuid});
        return;
    }
    case CREATE_ROOM: {
        if (rec_event.payload.contains("idr"))
            updateRoom(ecs, rec_event, rooms, tags, children, stages);
        else
            createRoom(ecs, rec_event, rooms, tags, children, stages);
        return;
    }
    case JOIN_ROOM: {
        joinRoom(ecs, rec_event, rooms, tags, children, stages);
        return;
    }
    case LAUNCH_GAME: {
        launchGame(ecs, rec_event, rooms, tags, children);
        return;
    }
    case SV_CREATE_PLAYER: {
        playerIsCreated(ecs, rec_event, rooms, tags, children, stages);
        return;
    }
    case CL_SHOOT: {
        playerShoot(ecs, rec_event, rooms, tags, children);
        return;
    }
    case SV_GAME_OVER: {
        gameOver(ecs, rec_event, rooms, tags);
        return;
    }
    case GET_ROOM: {
        getRoom(ecs, rec_event, rooms, tags, stages);
        return;
    }
    case GET_STAGE: {
        getStage(ecs, rec_event, util);
        return;
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
