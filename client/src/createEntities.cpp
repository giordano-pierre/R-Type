/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/
#include "createEntities.hpp"
#include "RequestEvent.hpp"
#include "buttonFunctions.hpp"
#include "ecsObjects.hpp"
#include <iostream>

namespace rtype::client {

void createGameEntities(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Velocity>(back1, {-1, 0});
    ecs.add_component<Tag>(back1, {BACKGROUND});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back1, {myWindow._myTextures.getTexture(
                    "assets/images/background/background_mountain.jpg"),
                {675, 360},
                {675, 360},
                1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Position>(back2, {serverSize.x / float(2) + serverSize.x,
                                        serverSize.y / float(2)});
    ecs.add_component<Velocity>(back2, {-1, 0});
    ecs.add_component<Tag>(back2, {BACKGROUND});
    ecs.add_component<Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back2, {myWindow._myTextures.getTexture(
                    "assets/images/background/background_mountain.jpg"),
                {675, 360},
                {675, 360},
                1});

    // Entity player1 = ecs.spawn_entity();
    // ecs.add_component<Position>(player1, {float(100), serverSize.y /
    // float(2)}); ecs.add_component<Velocity>(player1, {0, 0});
    // ecs.add_component<Playable>(player1, {1});
    // ecs.add_component<Tag>(player1, {PLAYER});
    // ecs.add_component<Hitbox>(player1, {{0.1, 0.12}});
    // ecs.add_component<Drawable>(
    //     player1,
    //     {myWindow._myTextures.getTexture("assets/images/ship/red_ship.png"),
    //      {395, 250},
    //      {395, 250},
    //      1,
    //      1});
}

void createMenuEntities(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Tag>(back1, {MENU});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(back1,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/background/back_menu.jpg"),
                                 {4608, 3456},
                                 {768, 432},
                                 48});

    Entity startB = ecs.spawn_entity();
    ecs.add_component<Position>(
        startB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(startB, {MENU});
    ecs.add_component<Hitbox>(startB, {{float(1) / 3, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("START")});
    texts.insert({"FR", std::make_shared<std::string>("COMMENCER")});
    ecs.add_component<Text>(
        startB, {texts, myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(startB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        startB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        startB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 [](ECS &ecs, Entity) {
                    ecs.post<DeleteEvent>({MENU});
                    ecs.post<CreationEvent>({MPLAYER});
                 }});

    Entity customB = ecs.spawn_entity();
    ecs.add_component<Position>(
        customB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(customB, {MENU});
    ecs.add_component<Hitbox>(customB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("CUSTOM")});
    texts.insert({"FR", std::make_shared<std::string>("PERSONNALISER")});
    ecs.add_component<Text>(customB, {texts,
                                      myWindow._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(customB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        customB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        customB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  [](ECS &ecs, Entity) {
                      std::cout << "Custom your ship!" << std::endl;
                  }});

    Entity configB = ecs.spawn_entity();
    ecs.add_component<Position>(
        configB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 5});
    ecs.add_component<Tag>(configB, {MENU});
    ecs.add_component<Hitbox>(configB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("CONFIGS")});
    texts.insert({"FR", std::make_shared<std::string>("PARAMETRES")});
    ecs.add_component<Text>(configB, {texts,
                                      myWindow._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(configB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        configB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        configB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  [](ECS &ecs, Entity) {
                      ecs.post<DeleteEvent>({MENU});
                      ecs.post<CreationEvent>({CONFIG});
                      ecs.post<CreationEvent>({CGENERAL});
                  }});

    Entity quitB = ecs.spawn_entity();
    ecs.add_component<Position>(
        quitB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(quitB, {MENU});
    ecs.add_component<Hitbox>(quitB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("QUIT")});
    texts.insert({"FR", std::make_shared<std::string>("QUITTER")});
    ecs.add_component<Text>(quitB, {texts,
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(quitB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        quitB, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        quitB,
        {myWindow._myTextures.getTexture(
             "assets/images/utils/button_config1_act.png"),
         [](ECS &ecs, Entity) { ecs.post<InputEvent>({sf::Event(), QUIT}); }});
}


void createMenuPlayerEntities(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Tag>(back1, {MPLAYER});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(back1,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/background/back_menu.jpg"),
                                 {4608, 3456},
                                 {768, 432},
                                 48});

    Entity Player1B = ecs.spawn_entity();
    ecs.add_component<Position>(
        Player1B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(Player1B, {MPLAYER});
    ecs.add_component<Hitbox>(Player1B, {{float(1) / 3, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("1 PLAYER")});
    texts.insert({"FR", std::make_shared<std::string>("1 JOUEUR")});
    ecs.add_component<Text>(
        Player1B, {texts, myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(Player1B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        Player1B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        Player1B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(startGame1P)});

    Entity Player2B = ecs.spawn_entity();
    ecs.add_component<Position>(
        Player2B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(Player2B, {MPLAYER});
    ecs.add_component<Hitbox>(Player2B, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("2 PLAYER")});
    texts.insert({"FR", std::make_shared<std::string>("2 JOUEUR")});
    ecs.add_component<Text>(Player2B, {texts,
                                      myWindow._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(Player2B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        Player2B, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        Player2B, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  std::function<void(ECS &, Entity)>(startGame2P)});

    Entity MultiB = ecs.spawn_entity();
    ecs.add_component<Position>(
        MultiB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 5});
    ecs.add_component<Tag>(MultiB, {MPLAYER});
    ecs.add_component<Hitbox>(MultiB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("MULTIPLAYER")});
    texts.insert({"FR", std::make_shared<std::string>("MULTIJOUEUR")});
    ecs.add_component<Text>(MultiB, {texts,
                                      myWindow._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(MultiB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        MultiB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        MultiB, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  std::function<void(ECS &, Entity)>(startGameMP)});

    Entity backB = ecs.spawn_entity();
    ecs.add_component<Position>(
        backB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(backB, {MPLAYER});
    ecs.add_component<Hitbox>(backB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("BACK")});
    texts.insert({"FR", std::make_shared<std::string>("RETOUR")});
    ecs.add_component<Text>(backB, {texts,
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(backB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        backB, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        backB,
        {myWindow._myTextures.getTexture(
             "assets/images/utils/button_config1_act.png"),
         [](ECS &ecs, Entity) {
            ecs.post<DeleteEvent>({MPLAYER});
            ecs.post<CreationEvent>({MENU});
         }});
}

void createConfigEntities(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Tag>(back1, {CONFIG});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(back1,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/background/back_menu.jpg"),
                                 {4608, 3456},
                                 {768, 432},
                                 48});
    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back2, {serverSize.x / float(2), serverSize.y * float(0.9) / float(2)});
    ecs.add_component<Tag>(back2, {CONFIG});
    ecs.add_component<Hitbox>(back2, {{1, 0.9}, false});
    ecs.add_component<Drawable>(
        back2, {myWindow._myTextures.getTexture(
                    "assets/images/background/back_config.png"),
                {512, 288},
                {512, 288},
                1,
                1});

    Entity generalB = ecs.spawn_entity();
    ecs.add_component<Position>(generalB,
                                {float(serverSize.x) / 12 * float(7.11),
                                 float(serverSize.y) / 10 * float(2.6)});
    ecs.add_component<Tag>(generalB, {CONFIG});
    ecs.add_component<Hitbox>(generalB, {{float(1) / 4, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("General")});
    texts.insert({"FR", std::make_shared<std::string>("General")});
    ecs.add_component<Text>(
        generalB, {texts, myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(generalB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        generalB, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        generalB, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({CPLAYER1});
                       ecs.post<DeleteEvent>({CPLAYER2});
                       ecs.post<CreationEvent>({CGENERAL});
                   },
                   1});
    press(ecs, generalB);

    Entity player1B = ecs.spawn_entity();
    ecs.add_component<Position>(player1B,
                                {float(serverSize.x) / 12 * float(6.14),
                                 float(serverSize.y) / 10 * float(3.9)});
    ecs.add_component<Tag>(player1B, {CONFIG});
    ecs.add_component<Hitbox>(player1B, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 1")});
    texts.insert({"FR", std::make_shared<std::string>("Joueur 1")});
    ecs.add_component<Text>(player1B, {texts,
                                       myWindow._font,
                                       {0.5, 0.5},
                                       0,
                                       40,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player1B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player1B, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player1B, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({CGENERAL});
                       ecs.post<DeleteEvent>({CPLAYER2});
                       ecs.post<CreationEvent>({CPLAYER1});
                   },
                   1});

    Entity player2B = ecs.spawn_entity();
    ecs.add_component<Position>(player2B,
                                {float(serverSize.x) / 12 * float(5.17),
                                 float(serverSize.y) / 10 * float(5.2)});
    ecs.add_component<Tag>(player2B, {CONFIG});
    ecs.add_component<Hitbox>(player2B, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 2")});
    texts.insert({"FR", std::make_shared<std::string>("Joueur 2")});
    ecs.add_component<Text>(player2B, {texts,
                                       myWindow._font,
                                       {0.5, 0.5},
                                       0,
                                       40,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player2B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player2B, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player2B, {myWindow._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({CGENERAL});
                       ecs.post<DeleteEvent>({CPLAYER1});
                       ecs.post<CreationEvent>({CPLAYER2});
                   },
                   1});

    Entity backB = ecs.spawn_entity();
    ecs.add_component<Position>(backB, {float(serverSize.x) / 12 * float(4.2),
                                        float(serverSize.y) / 10 * float(6.5)});
    ecs.add_component<Tag>(backB, {CONFIG});
    ecs.add_component<Hitbox>(backB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Back")});
    texts.insert({"FR", std::make_shared<std::string>("Retour")});
    ecs.add_component<Text>(backB, {texts,
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(backB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        backB, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        backB, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                    ecs.post<DeleteEvent>({CONFIG});
                    ecs.post<DeleteEvent>({CGENERAL});
                    ecs.post<DeleteEvent>({CPLAYER1});
                    ecs.post<DeleteEvent>({CPLAYER2});
                    ecs.post<CreationEvent>({MENU});
                }});
}

void createConfigGeneralEntites(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {CGENERAL});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("General")});
    texts.insert({"FR", std::make_shared<std::string>("General")});
    ecs.add_component<Text>(
        title, {texts, myWindow._font, {1, 1}, 0, 30, sf::Color::White});

    Entity interactP = ecs.spawn_entity();
    ecs.add_component<Position>(interactP,
                                {float(serverSize.x) / 8 * float(5.5),
                                 float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Tag>(interactP, {CGENERAL});
    ecs.add_component<Hitbox>(interactP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Interact")});
    texts.insert({"FR", std::make_shared<std::string>("Interagir")});
    ecs.add_component<Text>(interactP, {texts,
                                        myWindow._font,
                                        {1, 1},
                                        -0.1,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});

    Entity colorP = ecs.spawn_entity();
    ecs.add_component<Position>(colorP,
                                {float(serverSize.x) / 8 * float(5.5),
                                 float(serverSize.y) / 15 * float(7.6)});
    ecs.add_component<Tag>(colorP, {CGENERAL});
    ecs.add_component<Hitbox>(colorP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Colorblind mode")});
    texts.insert({"FR", std::make_shared<std::string>("Mode daltonien")});
    ecs.add_component<Text>(colorP, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity languageP = ecs.spawn_entity();
    ecs.add_component<Position>(languageP,
                                {float(serverSize.x) / 8 * float(5.1),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(languageP, {CGENERAL});
    ecs.add_component<Hitbox>(languageP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Language")});
    texts.insert({"FR", std::make_shared<std::string>("Langue")});
    ecs.add_component<Text>(languageP, {texts,
                                        myWindow._font,
                                        {1, 1},
                                        -0.1,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});

    Entity resP = ecs.spawn_entity();
    ecs.add_component<Position>(resP, {float(serverSize.x) / 8 * float(4.3),
                                       float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(resP, {CGENERAL});
    ecs.add_component<Hitbox>(resP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Window resolution")});
    texts.insert({"FR", std::make_shared<std::string>("taille de la fenetre")});
    ecs.add_component<Text>(resP, {texts,
                                   myWindow._font,
                                   {1, 1},
                                   -0.1,
                                   30,
                                   sf::Color::White,
                                   sf::Text::Style::Regular});

    Entity interactB = ecs.spawn_entity();
    ecs.add_component<Position>(
        interactB,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Tag>(interactB, {CGENERAL});
    ecs.add_component<Hitbox>(interactB, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(ENTER)->second.second});
    ecs.add_component<Text>(interactB, {texts,
                                        myWindow._font,
                                        {1, 1},
                                        0,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});
    ecs.add_component<Drawable>(interactB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        interactB, {myWindow._myTextures.getTexture(
                        "assets/images/utils/button_config2_sel.png"),
                    std::function<void(ECS &, Entity)>(select),
                    std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        interactB,
        {myWindow._myTextures.getTexture(
             "assets/images/utils/button_config2_act.png"),
         [](ECS &ecs, Entity i) {
             press(ecs, i);
             ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
             ecs.post<ChangeKey>({ENTER, i});
         }});

    Entity colorB = ecs.spawn_entity();
    ecs.add_component<Position>(
        colorB,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(7.6)});
    ecs.add_component<Tag>(colorB, {CGENERAL});
    ecs.add_component<Hitbox>(colorB, {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Drawable>(colorB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/toggle_config.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        colorB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/toggle_config_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        colorB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/toggle_config_act.png"),
                 std::function<void(ECS &, Entity)>(swapColorblind)});

    Entity res1B = ecs.spawn_entity();
    ecs.add_component<Position>(res1B,
                                {float(serverSize.x) / 8 * float(7.3),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res1B, {CGENERAL});
    ecs.add_component<Hitbox>(res1B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("1920 x 1080")});
    ecs.add_component<Text>(res1B, {texts,
                                    myWindow._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res1B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res1B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res1B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize1920), 2});
    if (myWindow._size.x == 1920)
        press(ecs, res1B);

    Entity res2B = ecs.spawn_entity();
    ecs.add_component<Position>(res2B,
                                {float(serverSize.x) / 8 * float(6.5),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res2B, {CGENERAL});
    ecs.add_component<Hitbox>(res2B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("1440 x 810")});
    ecs.add_component<Text>(res2B, {texts,
                                    myWindow._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res2B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res2B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res2B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize1440), 2});
    if (myWindow._size.x == 1440)
        press(ecs, res2B);

    Entity res3B = ecs.spawn_entity();
    ecs.add_component<Position>(res3B,
                                {float(serverSize.x) / 8 * float(5.7),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res3B, {CGENERAL});
    ecs.add_component<Hitbox>(res3B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("960 x 540")});
    ecs.add_component<Text>(res3B, {texts,
                                    myWindow._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res3B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res3B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res3B, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize960), 2});
    if (myWindow._size.x == 960)
        press(ecs, res3B);

    Entity lang1B = ecs.spawn_entity();
    ecs.add_component<Position>(lang1B,
                                {float(serverSize.x) / 8 * float(7.3),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(lang1B, {CGENERAL});
    ecs.add_component<Hitbox>(lang1B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("FR")});
    ecs.add_component<Text>(lang1B, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     0,
                                     20,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(lang1B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        lang1B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config2_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        lang1B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config2_act.png"),
                 std::function<void(ECS &, Entity)>(langFR), 3});
    if (myWindow._lang == "FR")
        press(ecs, lang1B);

    Entity lang2B = ecs.spawn_entity();
    ecs.add_component<Position>(lang2B,
                                {float(serverSize.x) / 8 * float(6.5),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(lang2B, {CGENERAL});
    ecs.add_component<Hitbox>(lang2B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("EN")});
    ecs.add_component<Text>(lang2B, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     0,
                                     20,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(lang2B,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        lang2B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config2_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        lang2B, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config2_act.png"),
                 std::function<void(ECS &, Entity)>(langEN), 3});
    if (myWindow._lang == "EN")
        press(ecs, lang2B);

    Entity resetB = ecs.spawn_entity();
    ecs.add_component<Position>(resetB,
                                {float(serverSize.x) / 12 * float(2.95),
                                 float(serverSize.y) / 10 * float(8.2)});
    ecs.add_component<Tag>(resetB, {CGENERAL});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     myWindow._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetG)});
}

void createConfigPlayer1Entites(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {CPLAYER1});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("Keyboard")});
    texts.insert({"FR", std::make_shared<std::string>("Clavier")});
    ecs.add_component<Text>(
        title, {texts, myWindow._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param1,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(param1, {CPLAYER1});
    ecs.add_component<Hitbox>(param1, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Top")});
    texts.insert({"FR", std::make_shared<std::string>("Haut")});
    ecs.add_component<Text>(param1, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Position>(param2, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(param2, {CPLAYER1});
    ecs.add_component<Hitbox>(param2, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Down")});
    texts.insert({"FR", std::make_shared<std::string>("Bas")});
    ecs.add_component<Text>(param2, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param3,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(param3, {CPLAYER1});
    ecs.add_component<Hitbox>(param3, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Left")});
    texts.insert({"FR", std::make_shared<std::string>("Gauche")});
    ecs.add_component<Text>(param3, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Position>(param4, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(param4, {CPLAYER1});
    ecs.add_component<Hitbox>(param4, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Right")});
    texts.insert({"FR", std::make_shared<std::string>("Droite")});
    ecs.add_component<Text>(param4, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param5,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(param5, {CPLAYER1});
    ecs.add_component<Hitbox>(param5, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Tir")});
    ecs.add_component<Text>(param5, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Position>(param6, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(param6, {CPLAYER1});
    ecs.add_component<Hitbox>(param6, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Super shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Super tir")});
    ecs.add_component<Text>(param6, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(button1, {CPLAYER1});
    ecs.add_component<Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(UP1P)->second.second});
    ecs.add_component<Text>(button1, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button1,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button1, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button1, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({UP1P, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Position>(button2, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(button2, {CPLAYER1});
    ecs.add_component<Hitbox>(button2, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(DOWN1P)->second.second});
    ecs.add_component<Text>(button2, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button2,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({DOWN1P, i});
                  }});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button3,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(button3, {CPLAYER1});
    ecs.add_component<Hitbox>(button3, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(LEFT1P)->second.second});
    ecs.add_component<Text>(button3, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button3,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button3, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button3, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({LEFT1P, i});
                  }});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Position>(button4, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(button4, {CPLAYER1});
    ecs.add_component<Hitbox>(button4, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(RIGHT1P)->second.second});
    ecs.add_component<Text>(button4, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button4,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button4, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button4, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({RIGHT1P, i});
                  }});

    Entity button5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button5,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(button5, {CPLAYER1});
    ecs.add_component<Hitbox>(button5, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(SHOOT1)->second.second});
    ecs.add_component<Text>(button5, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button5,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button5, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button5, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({SHOOT1, i});
                  }});

    Entity button6 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button6,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(button6, {CPLAYER1});
    ecs.add_component<Hitbox>(button6, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT",
         myWindow._inputConfig.first.find(SUPERSHOOT1)->second.second});
    ecs.add_component<Text>(button6, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button6,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button6, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button6, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({SUPERSHOOT1, i});
                  }});

    Entity resetB = ecs.spawn_entity();
    ecs.add_component<Position>(resetB,
                                {float(serverSize.x) / 12 * float(2.95),
                                 float(serverSize.y) / 10 * float(8.2)});
    ecs.add_component<Tag>(resetB, {CPLAYER1});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     myWindow._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetP1)});
}

void createConfigPlayer2Entites(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {CPLAYER2});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("Keyboard")});
    texts.insert({"FR", std::make_shared<std::string>("Clavier")});
    ecs.add_component<Text>(
        title, {texts, myWindow._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param1,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(param1, {CPLAYER2});
    ecs.add_component<Hitbox>(param1, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Top")});
    texts.insert({"FR", std::make_shared<std::string>("Haut")});
    ecs.add_component<Text>(param1, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Position>(param2, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(param2, {CPLAYER2});
    ecs.add_component<Hitbox>(param2, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Down")});
    texts.insert({"FR", std::make_shared<std::string>("Bas")});
    ecs.add_component<Text>(param2, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param3,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(param3, {CPLAYER2});
    ecs.add_component<Hitbox>(param3, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Left")});
    texts.insert({"FR", std::make_shared<std::string>("Gauche")});
    ecs.add_component<Text>(param3, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Position>(param4, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(param4, {CPLAYER2});
    ecs.add_component<Hitbox>(param4, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Right")});
    texts.insert({"FR", std::make_shared<std::string>("Droite")});
    ecs.add_component<Text>(param4, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param5,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(param5, {CPLAYER2});
    ecs.add_component<Hitbox>(param5, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Tir")});
    ecs.add_component<Text>(param5, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Position>(param6, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(param6, {CPLAYER2});
    ecs.add_component<Hitbox>(param6, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Super shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Super tir")});
    ecs.add_component<Text>(param6, {texts,
                                     myWindow._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(button1, {CPLAYER2});
    ecs.add_component<Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(UP2P)->second.second});
    ecs.add_component<Text>(button1, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button1,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button1, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button1, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({UP2P, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Position>(button2, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(button2, {CPLAYER2});
    ecs.add_component<Hitbox>(button2, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(DOWN2P)->second.second});
    ecs.add_component<Text>(button2, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button2,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({DOWN2P, i});
                  }});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button3,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(button3, {CPLAYER2});
    ecs.add_component<Hitbox>(button3, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(LEFT2P)->second.second});
    ecs.add_component<Text>(button3, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button3,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button3, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button3, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({LEFT2P, i});
                  }});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Position>(button4, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(button4, {CPLAYER2});
    ecs.add_component<Hitbox>(button4, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(RIGHT2P)->second.second});
    ecs.add_component<Text>(button4, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button4,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button4, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button4, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({RIGHT2P, i});
                  }});

    Entity button5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button5,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(button5, {CPLAYER2});
    ecs.add_component<Hitbox>(button5, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myWindow._inputConfig.first.find(SHOOT2)->second.second});
    ecs.add_component<Text>(button5, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button5,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button5, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button5, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({SHOOT2, i});
                  }});

    Entity button6 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button6,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(button6, {CPLAYER2});
    ecs.add_component<Hitbox>(button6, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT",
         myWindow._inputConfig.first.find(SUPERSHOOT2)->second.second});
    ecs.add_component<Text>(button6, {texts,
                                      myWindow._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button6,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button6, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button6, {myWindow._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({SUPERSHOOT2, i});
                  }});

    Entity resetB = ecs.spawn_entity();
    ecs.add_component<Position>(resetB,
                                {float(serverSize.x) / 12 * float(2.95),
                                 float(serverSize.y) / 10 * float(8.2)});
    ecs.add_component<Tag>(resetB, {CPLAYER2});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     myWindow._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {myWindow._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {myWindow._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetP2)});
}

} // namespace rtype::client
