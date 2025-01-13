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
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._size = {1920, 1080};
    press(ecs, i);
}

void resize1440(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._size = {1440, 810};
    press(ecs, i);
}

void resize960(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._size = {960, 540};
    press(ecs, i);
}

void langFR(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._lang = "FR";
    press(ecs, i);
}

void langEN(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._lang = "EN";
    press(ecs, i);
}

void resetG(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._lang = "EN";
    myWindow._size = {1440, 810};
    initGeneralInput(myWindow._inputConfig.first);
    ecs.post<DeleteEvent>({M_C_GENERAL});
    ecs.post<CreationEvent>({M_C_GENERAL});
}

void resetP1(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    initPlay1Input(myWindow._inputConfig);
}

void resetP2(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    initPlay2Input(myWindow._inputConfig);
}

void startGame1P(ECS &ecs, Entity i) {
    // ecs.post<DeleteEvent>({MENU});
    // ecs.post<CreationEvent>({PLAYER});
    auto &myWindow = ecs.get_components<Window>()[0].value();
    nlohmann::json p_name = nlohmann::json::array();
    p_name.push_back("Player1");
    nlohmann::json p_color = nlohmann::json::array();
    p_color.push_back("red");

    ecs.post<RequestEvent>(
        {JOIN_ROOM, {{"r_name","test"}, {"p_name", p_name}, {"p_color", p_color}}});
}

void startGame2P(ECS &ecs, Entity i) {
    // ecs.post<DeleteEvent>({MENU});
    // ecs.post<CreationEvent>({PLAYER});
    auto &myWindow = ecs.get_components<Window>()[0].value();

    // ecs.post<RequestEvent>(
    //     {CLIENT_READY, {{"nb_player_max", 2}, {"name", myWindow._name1}}});
    // ecs.post<RequestEvent>(
    //     {CLIENT_READY, {{"nb_player_max", 2}, {"name", myWindow._name2}}});
}

void startGameMP(ECS &ecs, Entity i) {
    // ecs.post<DeleteEvent>({MENU});
    // ecs.post<CreationEvent>({PLAYER});
    auto &myWindow = ecs.get_components<Window>()[0].value();

    // ecs.post<RequestEvent>(
    //     {CLIENT_READY, {{"nb_player_max", 2}, {"name", myWindow._name1}}});
}

void swapColorblind(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    myWindow._colorblind = !myWindow._colorblind;
    press(ecs, i);
}

} // namespace rtype::client
