/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/

#include <iostream>

#include "createEntities.hpp"
#include "ecsObjects.hpp"

namespace Rtype::Client {

void createGameEntities(ECS &ecs)
{
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Velocity>(back1, {-1, 0});
    ecs.add_component<Tag>(back1, {BACKGROUND});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(back1, {myWindow._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Position>(back2, {serverSize.x / float(2) + serverSize.x, serverSize.y / float(2)});
    ecs.add_component<Velocity>(back2, {-1, 0});
    ecs.add_component<Tag>(back2, {BACKGROUND});
    ecs.add_component<Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Drawable>(back2, {myWindow._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity player1 = ecs.spawn_entity();
    ecs.add_component<Position>(player1, {float(100), serverSize.y / float(2)});
    ecs.add_component<Velocity>(player1, {0, 0});
    ecs.add_component<Playable>(player1, {1});
    ecs.add_component<Tag>(player1, {PLAYER});
    ecs.add_component<Hitbox>(player1, {{0.1, 0.12}});
    // ecs.add_component<Hitbox>(player1, {{-0.1, 0.18}});
    ecs.add_component<Drawable>(player1, {myWindow._myTextures.getTexture("assets/images/ship/red_ship.png"), {395, 250}, {395, 250}, 1});
    // ecs.add_component<Drawable>(player1, {myWindow._myTextures.getTexture("assets/images/ship/enemy_ship_1.png"), {2030, 1450}, {290, 290}, 35});
}

void createMenuEntities(ECS &ecs)
{
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity button = ecs.spawn_entity();
    ecs.add_component<Position>(button, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 2});
    ecs.add_component<Tag>(button, {MENU});
    ecs.add_component<Hitbox>(button, {{0.48, float(1) / 10}});
    ecs.add_component<Text>(button, {"START", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(button, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Selectable>(button, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Start the game !" << std::endl;}});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Position>(button2, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(button2, {MENU});
    ecs.add_component<Hitbox>(button2, {{0.48,float(1) / 10}});
    ecs.add_component<Text>(button2, {"CUSTOM", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button2, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Selectable>(button2, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Custom your ship !" << std::endl;}});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Position>(button3, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(button3, {MENU});
    ecs.add_component<Hitbox>(button3, {{0.48,float(1) / 10}});
    ecs.add_component<Text>(button3, {"CONFIGS", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button3, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Selectable>(button3, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Open Parameters !" << std::endl;}});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Position>(button4, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 5});
    ecs.add_component<Tag>(button4, {MENU});
    ecs.add_component<Hitbox>(button4, {{0.48, float(1) / 10}});
    ecs.add_component<Text>(button4, {"QUIT", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button4, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Selectable>(button4, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"),[](ECS &ecs){ecs.post<InputEvent>({sf::Event(), QUIT});}});
}

void createConfigEntities(ECS &ecs)
{
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param1, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 2});
    ecs.add_component<Rtype::Client::Tag>(param1, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param1, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param1, {"Press a button: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White});
    ecs.add_component<Rtype::Client::Drawable>(param1, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param2, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 3});
    ecs.add_component<Rtype::Client::Tag>(param2, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param2, {{0.48,float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param2, {"Pause the game: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param2, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param3, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 4});
    ecs.add_component<Rtype::Client::Tag>(param3, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param3, {{0.48,float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param3, {"Quit the game: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param3, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param4, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 5});
    ecs.add_component<Rtype::Client::Tag>(param4, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param4, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param4, {"Go back to menu: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param4, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param5, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 6});
    ecs.add_component<Rtype::Client::Tag>(param5, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param5, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param5, {"Move Up: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param5, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param6, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 7});
    ecs.add_component<Rtype::Client::Tag>(param6, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param6, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param6, {"Move Down: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param6, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param7 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param7, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 8});
    ecs.add_component<Rtype::Client::Tag>(param7, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param7, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param7, {"Move Left: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param7, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param8 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param8, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 9});
    ecs.add_component<Rtype::Client::Tag>(param8, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param8, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param8, {"Move Right: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param8, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param9 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param9, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 10});
    ecs.add_component<Rtype::Client::Tag>(param9, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param9, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param9, {"Shoot: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param9, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param10 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param10, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 11});
    ecs.add_component<Rtype::Client::Tag>(param10, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param10, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param10, {"Super Shoot: ", myWindow._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param10, {myWindow._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

}

}
