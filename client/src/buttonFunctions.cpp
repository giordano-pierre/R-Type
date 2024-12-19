/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#include "ECS/ECS.hpp"
#include "ecsObjects.hpp"
#include "RequestEvent.hpp"

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
    ecs.post<DeleteEvent>({CGENERAL});
    ecs.post<CreateEvent>({CGENERAL});
}

void resetP1(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    initPlay1Input(myWindow._inputConfig);
}

void resetP2(ECS &ecs, Entity i) {
    auto &myWindow = ecs.get_components<Window>()[0].value();

    initPlay2Input(myWindow._inputConfig);
}

void startGame(ECS &ecs, Entity i)
{
    const auto &players = ecs.get_components<Playable>();

    for (size_t i = 0; i < players.size(); ++i) {
        const auto &play = players[i];

        if (play)
            ecs.post<RequestEvent>({CLIENT_READY, {
                    {"nb_player_max", 1},
                    {"name", play.value()._name}
                }});
    }
}

} // namespace rtype::client
