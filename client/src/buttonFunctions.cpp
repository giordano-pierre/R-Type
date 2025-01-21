/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** buttonFunctions
*/

#include "ECS/ECS.hpp"
#include "ecsObjects.hpp"
#include "events/RequestEvent.hpp"
#include <iostream>

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

void cyclePlayerColor(ECS &ecs) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();

    static const std::vector<sf::Color> colors = {
        sf::Color(253, 20, 175),
        sf::Color(255, 166, 208),
        sf::Color(243, 158, 108),
        sf::Color(255, 249, 148),
        sf::Color(140, 249, 147),
        sf::Color(104, 196, 249),
        sf::Color(81, 101, 235),
        sf::Color(186, 109, 245)
    };

    std::string &currentColor =
        (playerInfo._customPlayer == 1) ? playerInfo._color1 : playerInfo._color2;

    size_t colorIndex = 0;
    for (size_t i = 0; i < colors.size(); ++i) {
        std::ostringstream oss;
        oss << static_cast<int>(colors[i].r) << ","
            << static_cast<int>(colors[i].g) << ","
            << static_cast<int>(colors[i].b);

        if (currentColor == oss.str()) {
            colorIndex = (i + 1) % colors.size();
            break;
        }
    }

    const sf::Color &newColor = colors[colorIndex];
    std::ostringstream newColorStr;
    newColorStr << static_cast<int>(newColor.r) << ","
                << static_cast<int>(newColor.g) << ","
                << static_cast<int>(newColor.b);
    currentColor = newColorStr.str();

    auto &drawableComponents = ecs.get_components<Drawable>();
    for (size_t i = 0; i < drawableComponents.size(); ++i) {
        if (!drawableComponents[i]) continue;

        auto &drawable = drawableComponents[i].value();

        if (drawable._sprite.getTexture()->getSize() == sf::Vector2u(395, 250)) {
            drawable._sprite.setColor(newColor);
            break;
        }
    }
}

void cyclePlayerShip(ECS &ecs) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();

    static const std::vector<std::string> shipTextures = {
        "assets/images/ship/red_ship.png",
        "assets/images/ship/green_ship.png",
        "assets/images/ship/grey_ship.png",
        "assets/images/ship/cat.png"
    };

    std::string &currentSpritePath =
        (playerInfo._customPlayer == 1) ? playerInfo._spritePath1 : playerInfo._spritePath2;

    auto it = std::find(shipTextures.begin(), shipTextures.end(), currentSpritePath);
    if (it != shipTextures.end()) {
        size_t nextIndex = (std::distance(shipTextures.begin(), it) + 1) % shipTextures.size();
        currentSpritePath = shipTextures[nextIndex];
    } else {
        currentSpritePath = shipTextures[0];
    }

    std::cout << "Player sprite updated to: " << currentSpritePath << std::endl;
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
    // ecs.post<DeleteEvent>({M_PLAYER});
    // ecs.post<CreationEvent>({M_ROOM});
    ecs.post<RequestEvent>({GET_ROOM, {}});
}

void selectTwoPlayer(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();

    playerInfo._nbPlayer = 2;
    // ecs.post<DeleteEvent>({M_PLAYER});
    // ecs.post<CreationEvent>({M_ROOM});
    ecs.post<RequestEvent>({GET_ROOM, {}});
}

void createRoom(ECS &ecs, Entity i) {
    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
    nlohmann::json p_name = nlohmann::json::array();
    nlohmann::json p_color = nlohmann::json::array();
    p_name.push_back(playerInfo._name1);
    p_color.push_back(playerInfo._color1);
    if (playerInfo._nbPlayer == 2) {
        p_name.push_back(playerInfo._name2);
        p_color.push_back(playerInfo._color2);
    }

    ecs.post<RequestEvent>({CREATE_ROOM,
                            {{"r_name", "test"},
                             {"p_name", p_name},
                             {"p_color", p_color},
                             {"nbp", playerInfo._nbPlayer}}});
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
