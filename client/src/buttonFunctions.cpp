/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#include "ECS/ECS.hpp"
#include "ecsObjects.hpp"
#include "events/RequestEvent.hpp"

namespace rtype::client {

void select(ECS &ecs, Entity i) {
    auto &sel = ecs.get_components<Selectable>();

    if (i < sel.size() && sel[i]) {
        sel[i].value()._display = true;
    }
}

void deselect(ECS &ecs, Entity i) {
    auto &sel = ecs.get_components<Selectable>();

    if (i < sel.size() && sel[i]) {
        sel[i].value()._display = false;
    }
}

void press(ECS &ecs, Entity i) {
    auto &press = ecs.get_components<Pressable>();
    auto &draw = ecs.get_components<Drawable>();

    if (i < press.size() && press[i] && i < draw.size() && draw[i]) {
        if (!press[i].value()._isPressed)
            draw[i].value()._sprite.setTexture(*press[i].value()._texture);
        else
            draw[i].value()._sprite.setTexture(*draw[i].value()._texture);
        press[i].value()._isPressed = !press[i].value()._isPressed;
    }
}

void resize1920(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._size = {1920, 1080};
    press(ecs, i);
}

void resize1440(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._size = {1440, 810};
    press(ecs, i);
}

void resize960(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._size = {960, 540};
    press(ecs, i);
}

void langFR(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._lang = "FR";
    press(ecs, i);
}

void langEN(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._lang = "EN";
    press(ecs, i);
}

void resetG(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._lang = "EN";
    myConfig._size = {1440, 810};
    initGeneralInput(myConfig._inputConfig.first);
    ecs.post<DeleteEvent>({M_C_GENERAL});
    ecs.post<CreationEvent>({M_C_GENERAL});
}

void resetP1(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    initPlay1Input(myConfig._inputConfig);
}

void resetP2(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    initPlay2Input(myConfig._inputConfig);
}

void swapColorblind(ECS &ecs, Entity i) {
    auto &myConfig = ecs.get_components<Configs>()[0].value();

    myConfig._colorblind = !myConfig._colorblind;
    press(ecs, i);
}

void selectOnePlayer(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();

    playerInfo._nbPlayer = 1;
    ecs.post<RequestEvent>({GET_ROOM, {}});
}

void selectTwoPlayer(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();

    playerInfo._nbPlayer = 2;
    ecs.post<RequestEvent>({GET_ROOM, {}});
}

void createRoom(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
    auto &myRoom = ecs.get_components<Room>()[0].value();
    nlohmann::json p_name = nlohmann::json::array();
    nlohmann::json p_color = nlohmann::json::array();

    p_name.push_back(playerInfo._name1);
    p_color.push_back(playerInfo._color1);
    if (playerInfo._nbPlayer == 2) {
        p_name.push_back(playerInfo._name2);
        p_color.push_back(playerInfo._color2);
    }
    if (myRoom._idRoom.empty()) {
        ecs.post<RequestEvent>({CREATE_ROOM,
                                {{"r_name", myRoom._name.get()->data()},
                                {"st", myRoom._levelFile},
                                {"diff", myRoom._diff},
                                {"p_name", p_name},
                                {"p_color", p_color},
                                {"nbp", playerInfo._nbPlayer}}});
    } else {
        ecs.post<RequestEvent>({CREATE_ROOM,
                                {{"idr", myRoom._idRoom},
                                 {"r_name",myRoom._name.get()->data()},
                                 {"st", myRoom._levelFile},
                                 {"diff", myRoom._diff},
                                 {"p_name", p_name},
                                 {"p_color", p_color},
                                 {"nbp", playerInfo._nbPlayer}}});
    }
}

void joinRoom(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
    auto &tag = ecs.get_components<Tag>()[i].value();
    nlohmann::json p_name = nlohmann::json::array();
    nlohmann::json p_color = nlohmann::json::array();
    p_name.push_back(playerInfo._name1);
    p_color.push_back(playerInfo._color1);
    if (playerInfo._nbPlayer == 2) {
        p_name.push_back(playerInfo._name2);
        p_color.push_back(playerInfo._color2);
    }

    ecs.post<RequestEvent>({JOIN_ROOM,
                            {{"idr", tag._id},
                             {"p_name", p_name},
                             {"p_color", p_color},
                             {"nbp", playerInfo._nbPlayer}}});
}

void selectDiff1(ECS &ecs, Entity i) {
    auto &myRoom = ecs.get_components<Room>()[0].value();

    myRoom._diff = 1;
    press(ecs, i);
}

void selectDiff2(ECS &ecs, Entity i) {
    auto &myRoom = ecs.get_components<Room>()[0].value();

    myRoom._diff = 2;
    press(ecs, i);
}

void selectDiff3(ECS &ecs, Entity i) {
    auto &myRoom = ecs.get_components<Room>()[0].value();

    myRoom._diff = 3;
    press(ecs, i);
}

void selectLevel(ECS &ecs, Entity i) {
    auto &myRoom = ecs.get_components<Room>()[0].value();
    auto &tag = ecs.get_components<Tag>()[i].value();

    myRoom._levelFile = tag._id;
    press(ecs, i);
}

// void startGame2P(ECS &ecs, Entity i) {
//     // ecs.post<DeleteEvent>({MENU});
//     // ecs.post<CreationEvent>({PLAYER});
//     // auto &myWindow = ecs.get_components<Window>()[0].value();

//     // ecs.post<RequestEvent>(
//     //     {CLIENT_READY, {{"nb_player_max", 2}, {"name",
//     myWindow._name1}}});
//     // ecs.post<RequestEvent>(
//     //     {CLIENT_READY, {{"nb_player_max", 2}, {"name",
//     myWindow._name2}}});
// }

// void startGameMP(ECS &ecs, Entity i) {
//     // ecs.post<DeleteEvent>({MENU});
//     // ecs.post<CreationEvent>({PLAYER});
//     // auto &myWindow = ecs.get_components<Window>()[0].value();

//     // ecs.post<RequestEvent>(
//     //     {CLIENT_READY, {{"nb_player_max", 2}, {"name",
//     myWindow._name1}}});
// }

} // namespace rtype::client
