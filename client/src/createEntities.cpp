/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/
#include "createEntities.hpp"
#include "buttonFunctions.hpp"
#include "ecsObjects.hpp"
#include "events/RequestEvent.hpp"
#include "protocol.hpp"
#include <iostream>

namespace rtype::client {

void createGameEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj) {
    const auto &serverSize = myConfig._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Velocity>(back1, {-1, 0});
    ecs.add_component<Tag>(back1, {});
    ecs.add_component<Scene>(back1, {GAME});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back1, {SFMLObj._myTextures.getTexture(
                    "assets/images/background/background_mountain.jpg"),
                {675, 360},
                {675, 360},
                1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Position>(back2, {serverSize.x / float(2) + serverSize.x,
                                        serverSize.y / float(2)});
    ecs.add_component<Velocity>(back2, {-1, 0});
    ecs.add_component<Tag>(back2, {});
    ecs.add_component<Scene>(back2, {GAME});
    ecs.add_component<Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back2, {SFMLObj._myTextures.getTexture(
                    "assets/images/background/background_mountain.jpg"),
                {675, 360},
                {675, 360},
                1});
    Entity healthBar = ecs.spawn_entity();

    ecs.add_component<Position>(
        healthBar,
        {serverSize.x * float(1) / 7, serverSize.y * float(1) / 11});

    ecs.add_component<Tag>(healthBar, {});
    ecs.add_component<Scene>(healthBar, {GAME});
    float healthBarWidth = serverSize.x * (1.0 / 8.0);
    float healthBarHeight = serverSize.y * (1.0 / 16.0);

    ecs.add_component<Hitbox>(healthBar,
                              {{1.0 / 8, 1.0 / 16},
                               true,
                               {healthBarWidth, healthBarHeight},
                               {healthBarWidth, healthBarHeight},
                               false});
    ecs.add_component<Drawable>(
        healthBar,
        {SFMLObj._myTextures.getTexture("assets/images/utils/full_life.png"),
         {316, 71},
         {316, 71},
         2});
}

void createCustomEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj) {

    auto serverSize = myConfig._serverSize;
    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Tag>(back1, {});
    ecs.add_component<Scene>(back1, {CUSTOM});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back1, {SFMLObj._myTextures.getTexture(
                    "assets/images/background/custom.jpg"),
                {1434, 666},
                {1434, 666},
                1});

    Entity arrow1 = ecs.spawn_entity();
    ecs.add_component<Position>(arrow1, {serverSize.x * 0.05f, serverSize.y / 2.0f});
    ecs.add_component<Tag>(arrow1, {});
    ecs.add_component<Scene>(arrow1, {CUSTOM});

    ecs.add_component<Hitbox>(
        arrow1,
        {{float(1) / 6, float(1) / 4},
         true,
         {639 * (1.0f / 6.0f), 420 * (1.0f / 4.0f)},
         {639 * (1.0f / 6.0f), 420 * (1.0f / 4.0f)},
         false});
    ecs.add_component<Drawable>(arrow1,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/arrow_1.png"),
                                 {639, 420},
                                 {639, 420},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        arrow1, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/arrow_1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        arrow1,
        Pressable{
            SFMLObj._myTextures.getTexture("assets/images/utils/arrow_1.png"),
            [&SFMLObj](ECS &ecs, Entity entity) {
                rtype::client::press(ecs, entity);
                std::cout << "J'ai cliqué sur la flèche gauche !" << std::endl;
                rtype::client::cyclePlayerColor(ecs);
            }});

    Entity arrow2 = ecs.spawn_entity();
    ecs.add_component<Tag>(arrow2, {});
    ecs.add_component<Scene>(arrow2, {CUSTOM});
    ecs.add_component<Drawable>(
        arrow2,
        {SFMLObj._myTextures.getTexture("assets/images/utils/arrow_2.png"),
         {639, 420},
         {639, 420},
         1,
         1});

    ecs.add_component<Hitbox>(
        arrow2,
        {{float(1) / 6, float(1) / 4},
         true,
         {639 * (1.0f / 6.0f), 420 * (1.0f / 4.0f)},
         {639 * (1.0f / 6.0f), 420 * (1.0f / 4.0f)},
         false});

    ecs.add_component<Position>(
        arrow2,
        {serverSize.x * 0.95f,
         serverSize.y / 2.0f});

    ecs.add_component<Selectable>(
        arrow2, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/arrow_2_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});

    ecs.add_component<Pressable>(
        arrow2,
        Pressable{
            SFMLObj._myTextures.getTexture("assets/images/utils/arrow_2.png"),
            [&SFMLObj](ECS &ecs, Entity entity) {
                rtype::client::press(ecs, entity);
                std::cout << "J'ai cliqué sur la flèche droite !" << std::endl;
                rtype::client::cyclePlayerShip(ecs);
                ecs.post<DeleteEvent>({CUSTOM});
                ecs.post<CreationEvent>({CUSTOM});
            }});

    Entity playerSprite = ecs.spawn_entity();

    float spriteWidth = serverSize.x * (1.0f / 4.0f);
    float spriteHeight = serverSize.y * (1.0f / 4.0f);

    ecs.add_component<Position>(
        playerSprite, {serverSize.x / 2.0f, serverSize.y / 2.0f});

    ecs.add_component<Hitbox>(
        playerSprite,
        {{1.0f / 4.0f, 1.0f / 4.0f},
         true,
         {spriteWidth, spriteHeight},
         {spriteWidth, spriteHeight},
         false});

    auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
    std::string spritePath = (playerInfo._customPlayer == 1) ? playerInfo._spritePath1 : playerInfo._spritePath2;

    ecs.add_component<Drawable>(
        playerSprite,
        {SFMLObj._myTextures.getTexture(spritePath),
         {395, 250},
         {395, 250},
         1,
         1});

    auto &drawable = ecs.get_components<Drawable>()[playerSprite].value();

    sf::Color playerColor;
    if (playerInfo._customPlayer == 1) {
        std::istringstream colorStream(playerInfo._color1);
        int r, g, b;
        char comma;
        colorStream >> r >> comma >> g >> comma >> b;
        playerColor = sf::Color(r, g, b);
    } else if (playerInfo._customPlayer == 2) {
        std::istringstream colorStream(playerInfo._color2);
        int r, g, b;
        char comma;
        colorStream >> r >> comma >> g >> comma >> b;
        playerColor = sf::Color(r, g, b);
    } else {
        playerColor = sf::Color::White;
    }

    drawable._sprite.setColor(playerColor);

    ecs.add_component<Tag>(playerSprite, {});
    ecs.add_component<Scene>(playerSprite, {CUSTOM});

    Entity backB = ecs.spawn_entity();
    ecs.add_component<Position>(backB, {serverSize.x * 0.2f, serverSize.y * 0.1f});
    ecs.add_component<Tag>(backB, {});
    ecs.add_component<Scene>(backB, {CUSTOM});

    ecs.add_component<Hitbox>(backB, {{float(1) / 4, float(1) / 10}});

    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("Back")});
    texts.insert({"FR", std::make_shared<std::string>("Retour")});
    ecs.add_component<Text>(backB, {texts,
                                    SFMLObj._font,
                                    {0.5f, 0.5f},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});

    ecs.add_component<Drawable>(
        backB,
        {SFMLObj._myTextures.getTexture("assets/images/utils/button_config1.png"),
         {402, 100},
         {402, 100},
         1,
         2});

    ecs.add_component<Selectable>(
        backB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});

    ecs.add_component<Pressable>(
        backB,
        Pressable{
            SFMLObj._myTextures.getTexture("assets/images/utils/button_config1_act.png"),
            [](ECS &ecs, Entity) {
                std::cout << "Returning to main menu..." << std::endl;
                ecs.post<DeleteEvent>({CUSTOM});
                ecs.post<CreationEvent>({M_GENERAL});
            }});

    Entity player1B = ecs.spawn_entity();
    ecs.add_component<Position>(player1B,
                                {float(serverSize.x) / 8 * float(6.5),
                                 float(serverSize.y) * 0.85f});
    ecs.add_component<Scene>(player1B, {CUSTOM});
    ecs.add_component<Hitbox>(player1B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 1")});
        texts.insert({"FR", std::make_shared<std::string>("Joueur 1")});
    ecs.add_component<Text>(player1B, {texts,
                                       SFMLObj._font,
                                       {0.5f, 0.5f},
                                       0,
                                       20,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player1B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player1B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config2_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player1B,
        Pressable{
            SFMLObj._myTextures.getTexture(
                "assets/images/utils/button_config2_act.png"),
            [](ECS &ecs, Entity entity) {
                rtype::client::press(ecs, entity);
                auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
                playerInfo._customPlayer = 1;
                std::cout << "Player 1 selected for customization." << std::endl;
                ecs.post<DeleteEvent>({CUSTOM});
                ecs.post<CreationEvent>({CUSTOM});
            },
            3});

    Entity player2B = ecs.spawn_entity();
    ecs.add_component<Position>(player2B,
                                {float(serverSize.x) / 8 * float(7.3),
                                 float(serverSize.y) * 0.85f});
    ecs.add_component<Tag>(player2B, {});
    ecs.add_component<Scene>(player2B, {CUSTOM});
    ecs.add_component<Hitbox>(player2B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 2")});
    texts.insert({"FR", std::make_shared<std::string>("Joueur 2")});
    ecs.add_component<Text>(player2B, {texts,
                                       SFMLObj._font,
                                       {0.5f, 0.5f},
                                       0,
                                       20,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player2B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player2B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config2_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player2B,
        Pressable{
            SFMLObj._myTextures.getTexture(
                "assets/images/utils/button_config2_act.png"),
            [](ECS &ecs, Entity entity) {
                rtype::client::press(ecs, entity);
                auto &playerInfo = ecs.get_components<PlayerInfo>()[0].value();
                playerInfo._customPlayer = 2;
                std::cout << "Player 2 selected for customization." << std::endl;
                ecs.post<DeleteEvent>({CUSTOM});
                ecs.post<CreationEvent>({CUSTOM});
            },
            3});

    if (playerInfo._customPlayer == 1) {
        press(ecs, player1B);
    } else if (playerInfo._customPlayer == 2) {
        press(ecs, player2B);
    }
}

void createMenuEntities(ECS &ecs, const Configs &myConfig,
                        SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Tag>(back1, {});
    ecs.add_component<Scene>(back1, {MENU});
    ecs.add_component<Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Drawable>(back1,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/background/back_menu.jpg"),
                                 {4608, 3456},
                                 {768, 432},
                                 48});
    ecs.add_component<rtype::client::Sound>(
        back1,
        {"assets/audio/epic_menu.ogg",
        rtype::client::SoundState::LOOP,
        50.0f});
}

void createMenuGeneralEntities(ECS &ecs, const Configs &myConfig,
                               SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity startB = ecs.spawn_entity();
    ecs.add_component<Position>(
        startB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(startB, {});
    ecs.add_component<Scene>(startB, {M_GENERAL});
    ecs.add_component<Hitbox>(startB, {{float(1) / 3, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("START")});
    texts.insert({"FR", std::make_shared<std::string>("COMMENCER")});
    ecs.add_component<Text>(
        startB, {texts, SFMLObj._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(startB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        startB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        startB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 // std::function<void(ECS &, Entity)>(startGame1P)
                 [](ECS &ecs, Entity) {
                     ecs.post<RequestEvent>({Protocol::CONNECT, {}});
                     ecs.post<DeleteEvent>({M_GENERAL});
                     ecs.post<CreationEvent>({M_PLAYER});
                 }});

    Entity customB = ecs.spawn_entity();
    ecs.add_component<Position>(
        customB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(customB, {});
    ecs.add_component<Scene>(customB, {M_GENERAL});
    ecs.add_component<Hitbox>(customB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("CUSTOM")});
    texts.insert({"FR", std::make_shared<std::string>("PERSONNALISER")});
    ecs.add_component<Text>(customB, {texts,
                                      SFMLObj._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(customB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        customB, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        customB, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  [](ECS &ecs, Entity) {
                      std::cout << "Custom your ship!" << std::endl;
                      ecs.post<DeleteEvent>({M_GENERAL});
                      ecs.post<CreationEvent>({CUSTOM});
                  }});

    Entity configB = ecs.spawn_entity();
    ecs.add_component<Position>(
        configB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 5});
    ecs.add_component<Tag>(configB, {});
    ecs.add_component<Scene>(configB, {M_GENERAL});
    ecs.add_component<Hitbox>(configB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("CONFIGS")});
    texts.insert({"FR", std::make_shared<std::string>("PARAMETRES")});
    ecs.add_component<Text>(configB, {texts,
                                      SFMLObj._font,
                                      {0.5, 0.5},
                                      0,
                                      40,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(configB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        configB, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config1_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        configB, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config1_act.png"),
                  [](ECS &ecs, Entity) {
                      ecs.post<DeleteEvent>({M_GENERAL});
                      ecs.post<CreationEvent>({M_CONFIG});
                      ecs.post<CreationEvent>({M_C_GENERAL});
                  }});

    Entity quitB = ecs.spawn_entity();
    ecs.add_component<Position>(
        quitB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(quitB, {});
    ecs.add_component<Scene>(quitB, {M_GENERAL});
    ecs.add_component<Hitbox>(quitB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("QUIT")});
    texts.insert({"FR", std::make_shared<std::string>("QUITTER")});
    ecs.add_component<Text>(quitB, {texts,
                                    SFMLObj._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(quitB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        quitB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        quitB,
        {SFMLObj._myTextures.getTexture(
             "assets/images/utils/button_config1_act.png"),
         [](ECS &ecs, Entity) { ecs.post<InputEvent>({sf::Event(), QUIT}); }});
}

void createMenuPlayerEntities(ECS &ecs, const Configs &myConfig,
                              SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity player1B = ecs.spawn_entity();
    ecs.add_component<Position>(
        player1B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(player1B, {});
    ecs.add_component<Scene>(player1B, {M_PLAYER});
    ecs.add_component<Hitbox>(player1B, {{float(1) / 3, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("1 PLAYER")});
    texts.insert({"FR", std::make_shared<std::string>("1 JOUEUR")});
    ecs.add_component<Text>(
        player1B, {texts, SFMLObj._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(player1B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        player1B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player1B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   std::function<void(ECS &, Entity)>(selectOnePlayer)});

    Entity player2B = ecs.spawn_entity();
    ecs.add_component<Position>(
        player2B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(player2B, {});
    ecs.add_component<Scene>(player2B, {M_PLAYER});
    ecs.add_component<Hitbox>(player2B, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("2 PLAYER")});
    texts.insert({"FR", std::make_shared<std::string>("2 JOUEUR")});
    ecs.add_component<Text>(player2B, {texts,
                                       SFMLObj._font,
                                       {0.5, 0.5},
                                       0,
                                       40,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player2B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        player2B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player2B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   std::function<void(ECS &, Entity)>(selectTwoPlayer)});

    Entity quitB = ecs.spawn_entity();
    ecs.add_component<Position>(
        quitB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(quitB, {});
    ecs.add_component<Scene>(quitB, {M_PLAYER});
    ecs.add_component<Hitbox>(quitB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("BACK")});
    texts.insert({"FR", std::make_shared<std::string>("RETOUR")});
    ecs.add_component<Text>(quitB, {texts,
                                    SFMLObj._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(quitB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        quitB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        quitB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                    ecs.post<DeleteEvent>({M_PLAYER});
                    ecs.post<CreationEvent>({M_GENERAL});
                }});
}

void createMenuRoomEntities(ECS &ecs, const ReceiveEvent &rec_event,
                            const Configs &myConfig, SFMLObjects &SFMLObj,
                            PlayerInfo &playerInfo, Room &myRoom) {
    auto serverSize = myConfig._serverSize;

    Entity createRoomB = ecs.spawn_entity();
    ecs.add_component<Position>(
        createRoomB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
    ecs.add_component<Tag>(createRoomB, {});
    ecs.add_component<Scene>(createRoomB, {M_ROOM});
    ecs.add_component<Hitbox>(createRoomB, {{float(1) / 3, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("CREATE ROOM")});
    texts.insert({"FR", std::make_shared<std::string>("CREER UNE PARTIE")});
    ecs.add_component<Text>(createRoomB, {texts,
                                          SFMLObj._font,
                                          {0.5, 0.5},
                                          0,
                                          40,
                                          sf::Color::White,
                                          sf::Text::Style::Regular});
    ecs.add_component<Drawable>(createRoomB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        createRoomB, {SFMLObj._myTextures.getTexture(
                          "assets/images/utils/button_config1_sel.png"),
                      std::function<void(ECS &, Entity)>(select),
                      std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        createRoomB, {SFMLObj._myTextures.getTexture(
                          "assets/images/utils/button_config1_act.png"),
                      std::function<void(ECS &, Entity)>(createRoom)});

    Entity refreshRoomB = ecs.spawn_entity();
    ecs.add_component<Position>(
        refreshRoomB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(refreshRoomB, {});
    ecs.add_component<Scene>(refreshRoomB, {M_ROOM});
    ecs.add_component<Hitbox>(refreshRoomB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("REFRESH ROOMS")});
    texts.insert({"FR", std::make_shared<std::string>("RAFRAICHIR")});
    ecs.add_component<Text>(refreshRoomB, {texts,
                                           SFMLObj._font,
                                           {0.5, 0.5},
                                           0,
                                           40,
                                           sf::Color::White,
                                           sf::Text::Style::Regular});
    ecs.add_component<Drawable>(refreshRoomB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        refreshRoomB, {SFMLObj._myTextures.getTexture(
                           "assets/images/utils/button_config1_sel.png"),
                       std::function<void(ECS &, Entity)>(select),
                       std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        refreshRoomB,
        {SFMLObj._myTextures.getTexture(
             "assets/images/utils/button_config1_act.png"),
         [](ECS &ecs, Entity) { ecs.post<RequestEvent>({GET_ROOM, {}}); }});

    Entity quitB = ecs.spawn_entity();
    ecs.add_component<Position>(
        quitB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(quitB, {});
    ecs.add_component<Scene>(quitB, {M_ROOM});
    ecs.add_component<Hitbox>(quitB, {{float(1) / 3, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("BACK")});
    texts.insert({"FR", std::make_shared<std::string>("RETOUR")});
    ecs.add_component<Text>(quitB, {texts,
                                    SFMLObj._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(quitB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 1});
    ecs.add_component<Selectable>(
        quitB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        quitB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                    ecs.post<DeleteEvent>({M_ROOM});
                    ecs.post<CreationEvent>({M_PLAYER});
                }});

    std::vector<std::string> r_name = rec_event.payload["r_name"];
    std::vector<int> r_nbp = rec_event.payload["r_nbp"];
    std::vector<std::string> r_id = rec_event.payload["idr"];
    std::vector<std::string> r_stage = rec_event.payload["r_st"];
    bool isRoom = false;

    for (size_t i = 0; i < r_name.size(); i++) {
        isRoom = true;
        Entity roomB = ecs.spawn_entity();
        ecs.add_component<Position>(roomB,
                                    {float(serverSize.x) / 5 * float(3.5),
                                     float(serverSize.y) / 15 * (i + 5)});
        ecs.add_component<Tag>(roomB, {OTHER, r_id[i]});
        ecs.add_component<Scene>(roomB, {M_ROOM});
        ecs.add_component<Hitbox>(roomB, {{float(1) / 2, float(1) / 15}});
        texts.clear();
        texts.insert({"DEFAULT", std::make_shared<std::string>(r_name[i])});
        ecs.add_component<Text>(roomB, {texts,
                                        SFMLObj._font,
                                        {1, 1},
                                        0.05,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});
        ecs.add_component<Drawable>(roomB,
                                    {SFMLObj._myTextures.getTexture(
                                         "assets/images/utils/button_room.png"),
                                     {710, 64},
                                     {710, 64},
                                     1,
                                     1});
        ecs.add_component<Selectable>(
            roomB, {SFMLObj._myTextures.getTexture(
                        "assets/images/utils/button_room_sel.png"),
                    std::function<void(ECS &, Entity)>(select),
                    std::function<void(ECS &, Entity)>(deselect)});
        ecs.add_component<Pressable>(
            roomB, {SFMLObj._myTextures.getTexture(
                        "assets/images/utils/button_room.png"),
                    std::function<void(ECS &, Entity)>(joinRoom)});
        Entity level = ecs.spawn_entity();
        ecs.add_component<Position>(level,
                                    {float(serverSize.x) / 5 * float(3.5),
                                     float(serverSize.y) / 15 * (i + 5)});
        ecs.add_component<Tag>(level, {});
        ecs.add_component<Scene>(level, {M_ROOM});
        ecs.add_component<Hitbox>(level, {{float(1) / 2, float(1) / 15}});
        texts.clear();
        texts.insert({"DEFAULT", std::make_shared<std::string>(r_stage[i])});
        ecs.add_component<Text>(level, {texts,
                                        SFMLObj._font,
                                        {1, 1},
                                        0,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});
        Entity players = ecs.spawn_entity();
        ecs.add_component<Position>(players,
                                    {float(serverSize.x) / 5 * float(3.5),
                                     float(serverSize.y) / 15 * (i + 5)});
        ecs.add_component<Tag>(players, {});
        ecs.add_component<Scene>(players, {M_ROOM});
        ecs.add_component<Hitbox>(players, {{float(1) / 2, float(1) / 15}});
        texts.clear();
        texts.insert({"DEFAULT", std::make_shared<std::string>(
                                     std::to_string(r_nbp[i]) + " / 8")});
        ecs.add_component<Text>(players, {texts,
                                          SFMLObj._font,
                                          {1, 1},
                                          (-0.05),
                                          30,
                                          sf::Color::White,
                                          sf::Text::Style::Regular});
    }
    if (!isRoom) {
        Entity noRoom = ecs.spawn_entity();
        ecs.add_component<Position>(noRoom,
                                    {float(serverSize.x) / 5 * float(3.5),
                                     float(serverSize.y) / 15 * (8)});
        ecs.add_component<Tag>(noRoom, {});
        ecs.add_component<Scene>(noRoom, {M_ROOM});
        ecs.add_component<Hitbox>(noRoom, {{float(1) / 3, float(1) / 5}});
        texts.clear();
        texts.insert({"EN", std::make_shared<std::string>("NO ROOM")});
        texts.insert({"FR", std::make_shared<std::string>("AUCUNE PARTIE")});
        ecs.add_component<Text>(noRoom, {texts,
                                         SFMLObj._font,
                                         {1, 1},
                                         0,
                                         40,
                                         sf::Color::White,
                                         sf::Text::Style::Regular});
        ecs.add_component<Drawable>(
            noRoom, {SFMLObj._myTextures.getTexture(
                         "assets/images/utils/button_config2.png"),
                     {128, 64},
                     {128, 64},
                     1,
                     2});
    }
}

void createMenuInRoomEntities(ECS &ecs, const Configs &myConfig,
                              SFMLObjects &SFMLObj, Room &myRoom) {
    auto serverSize = myConfig._serverSize;

    if (myRoom._master) {
        Entity startB = ecs.spawn_entity();
        ecs.add_component<Position>(
            startB, {float(serverSize.x) / 5 * 4, float(serverSize.y) / 7 * 6});
        ecs.add_component<Tag>(startB, {});
        ecs.add_component<Scene>(startB, {M_IN_ROOM});
        ecs.add_component<Hitbox>(startB, {{float(1) / 3, float(1) / 10}});
        std::map<std::string, std::shared_ptr<std::string>> texts;
        texts.insert({"EN", std::make_shared<std::string>("START GAME")});
        texts.insert({"FR", std::make_shared<std::string>("COMMENCER")});
        ecs.add_component<Text>(
            startB,
            {texts, SFMLObj._font, {0.5, 0.5}, 0, 40, sf::Color::White});
        ecs.add_component<Drawable>(
            startB, {SFMLObj._myTextures.getTexture(
                         "assets/images/utils/button_config1.png"),
                     {402, 100},
                     {402, 100},
                     1,
                     1});
        ecs.add_component<Selectable>(
            startB, {SFMLObj._myTextures.getTexture(
                         "assets/images/utils/button_config1_sel.png"),
                     std::function<void(ECS &, Entity)>(select),
                     std::function<void(ECS &, Entity)>(deselect)});
        ecs.add_component<Pressable>(
            startB, {SFMLObj._myTextures.getTexture(
                         "assets/images/utils/button_config1_act.png"),
                     [](ECS &ecs, Entity) {
                         auto &myRoom = ecs.get_components<Room>()[0].value();
                         ecs.post<RequestEvent>(
                             {LAUNCH_GAME, {{"idr", myRoom._idRoom}}});
                     }});
    } else {
        Entity message = ecs.spawn_entity();
        ecs.add_component<Position>(message, {float(serverSize.x) / 5 * 4,
                                              float(serverSize.y) / 7 * 6});
        ecs.add_component<Tag>(message, {});
        ecs.add_component<Scene>(message, {M_IN_ROOM});
        ecs.add_component<Hitbox>(message, {{float(1) / 3, float(1) / 10}});
        std::map<std::string, std::shared_ptr<std::string>> texts;
        texts.insert({"EN", std::make_shared<std::string>("Waiting host")});
        texts.insert(
            {"FR", std::make_shared<std::string>("En attente de l'hote")});
        ecs.add_component<Text>(
            message,
            {texts, SFMLObj._font, {0.5, 0.5}, 0, 40, sf::Color::White});
        ecs.add_component<Drawable>(
            message, {SFMLObj._myTextures.getTexture(
                          "assets/images/utils/button_config1.png"),
                      {402, 100},
                      {402, 100},
                      1,
                      1});
    }
}

// void createMenuPlayerEntities(ECS &ecs, Window &myWindow) {
//     auto serverSize = myWindow._serverSize;

//     Entity player1B = ecs.spawn_entity();
//     ecs.add_component<Position>(
//         player1B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 3});
//     ecs.add_component<Tag>(player1B, {});
//     ecs.add_component<Scene>(player1B, {M_PLAYER});
//     ecs.add_component<Hitbox>(player1B, {{float(1) / 3, float(1) / 10}});
//     std::map<std::string, std::shared_ptr<std::string>> texts;
//     texts.insert({"EN", std::make_shared<std::string>("1 PLAYER")});
//     texts.insert({"FR", std::make_shared<std::string>("1 JOUEUR")});
//     ecs.add_component<Text>(
//         player1B, {texts, myWindow._font, {0.5, 0.5}, 0, 40,
//         sf::Color::White});
//     ecs.add_component<Drawable>(player1B,
//                                 {myWindow._myTextures.getTexture(
//                                      "assets/images/utils/button_config1.png"),
//                                  {402, 100},
//                                  {402, 100},
//                                  1,
//                                  1});
//     ecs.add_component<Selectable>(
//         player1B, {myWindow._myTextures.getTexture(
//                        "assets/images/utils/button_config1_sel.png"),
//                    std::function<void(ECS &, Entity)>(select),
//                    std::function<void(ECS &, Entity)>(deselect)});
//     ecs.add_component<Pressable>(
//         player1B, {myWindow._myTextures.getTexture(
//                        "assets/images/utils/button_config1_act.png"),
//                    std::function<void(ECS &, Entity)>(startGame1P)});

//     Entity player2B = ecs.spawn_entity();
//     ecs.add_component<Position>(
//         player2B, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
//     ecs.add_component<Tag>(player2B, {});
//     ecs.add_component<Scene>(player2B, {M_PLAYER});
//     ecs.add_component<Hitbox>(player2B, {{float(1) / 3, float(1) / 10}});
//     texts.clear();
//     texts.insert({"EN", std::make_shared<std::string>("2 PLAYER")});
//     texts.insert({"FR", std::make_shared<std::string>("2 JOUEUR")});
//     ecs.add_component<Text>(player2B, {texts,
//                                        myWindow._font,
//                                        {0.5, 0.5},
//                                        0,
//                                        40,
//                                        sf::Color::White,
//                                        sf::Text::Style::Regular});
//     ecs.add_component<Drawable>(player2B,
//                                 {myWindow._myTextures.getTexture(
//                                      "assets/images/utils/button_config1.png"),
//                                  {402, 100},
//                                  {402, 100},
//                                  1,
//                                  1});
//     ecs.add_component<Selectable>(
//         player2B, {myWindow._myTextures.getTexture(
//                        "assets/images/utils/button_config1_sel.png"),
//                    std::function<void(ECS &, Entity)>(select),
//                    std::function<void(ECS &, Entity)>(deselect)});
//     ecs.add_component<Pressable>(
//         player2B, {myWindow._myTextures.getTexture(
//                        "assets/images/utils/button_config1_act.png"),
//                    std::function<void(ECS &, Entity)>(startGame2P)});

//     Entity multiB = ecs.spawn_entity();
//     ecs.add_component<Position>(
//         multiB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 5});
//     ecs.add_component<Tag>(multiB, {});
//     ecs.add_component<Scene>(multiB, {M_PLAYER});
//     ecs.add_component<Hitbox>(multiB, {{float(1) / 3, float(1) / 10}});
//     texts.clear();
//     texts.insert({"EN", std::make_shared<std::string>("MULTIPLAYER")});
//     texts.insert({"FR", std::make_shared<std::string>("MULTIJOUEUR")});
//     ecs.add_component<Text>(multiB, {texts,
//                                      myWindow._font,
//                                      {0.5, 0.5},
//                                      0,
//                                      40,
//                                      sf::Color::White,
//                                      sf::Text::Style::Regular});
//     ecs.add_component<Drawable>(multiB,
//                                 {myWindow._myTextures.getTexture(
//                                      "assets/images/utils/button_config1.png"),
//                                  {402, 100},
//                                  {402, 100},
//                                  1,
//                                  1});
//     ecs.add_component<Selectable>(
//         multiB, {myWindow._myTextures.getTexture(
//                      "assets/images/utils/button_config1_sel.png"),
//                  std::function<void(ECS &, Entity)>(select),
//                  std::function<void(ECS &, Entity)>(deselect)});
//     ecs.add_component<Pressable>(
//         multiB, {myWindow._myTextures.getTexture(
//                      "assets/images/utils/button_config1_act.png"),
//                  std::function<void(ECS &, Entity)>(startGameMP)});

//     Entity backB = ecs.spawn_entity();
//     ecs.add_component<Position>(
//         backB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
//     ecs.add_component<Tag>(backB, {});
//     ecs.add_component<Scene>(backB, {M_PLAYER});
//     ecs.add_component<Hitbox>(backB, {{float(1) / 3, float(1) / 10}});
//     texts.clear();
//     texts.insert({"EN", std::make_shared<std::string>("BACK")});
//     texts.insert({"FR", std::make_shared<std::string>("RETOUR")});
//     ecs.add_component<Text>(backB, {texts,
//                                     myWindow._font,
//                                     {0.5, 0.5},
//                                     0,
//                                     40,
//                                     sf::Color::White,
//                                     sf::Text::Style::Regular});
//     ecs.add_component<Drawable>(backB,
//                                 {myWindow._myTextures.getTexture(
//                                      "assets/images/utils/button_config1.png"),
//                                  {402, 100},
//                                  {402, 100},
//                                  1,
//                                  1});
//     ecs.add_component<Selectable>(
//         backB, {myWindow._myTextures.getTexture(
//                     "assets/images/utils/button_config1_sel.png"),
//                 std::function<void(ECS &, Entity)>(select),
//                 std::function<void(ECS &, Entity)>(deselect)});
//     ecs.add_component<Pressable>(
//         backB, {myWindow._myTextures.getTexture(
//                     "assets/images/utils/button_config1_act.png"),
//                 [](ECS &ecs, Entity) {
//                     ecs.post<DeleteEvent>({M_PLAYER});
//                     ecs.post<CreationEvent>({M_GENERAL});
//                 }});
// }

void createConfigEntities(ECS &ecs, const Configs &myConfig,
                          SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Position>(
        back2, {serverSize.x / float(2), serverSize.y * float(0.9) / float(2)});
    ecs.add_component<Tag>(back2, {});
    ecs.add_component<Scene>(back2, {M_CONFIG});
    ecs.add_component<Hitbox>(back2, {{1, 0.9}, false});
    ecs.add_component<Drawable>(
        back2, {SFMLObj._myTextures.getTexture(
                    "assets/images/background/back_config.png"),
                {512, 288},
                {512, 288},
                1,
                1});

    Entity generalB = ecs.spawn_entity();
    ecs.add_component<Position>(generalB,
                                {float(serverSize.x) / 12 * float(7.11),
                                 float(serverSize.y) / 10 * float(2.6)});
    ecs.add_component<Tag>(generalB, {});
    ecs.add_component<Scene>(generalB, {M_CONFIG});
    ecs.add_component<Hitbox>(generalB, {{float(1) / 4, float(1) / 10}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("General")});
    texts.insert({"FR", std::make_shared<std::string>("General")});
    ecs.add_component<Text>(
        generalB, {texts, SFMLObj._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Drawable>(generalB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        generalB, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        generalB, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({M_C_PLAYER1});
                       ecs.post<DeleteEvent>({M_C_PLAYER2});
                       ecs.post<CreationEvent>({M_C_GENERAL});
                   },
                   1});
    press(ecs, generalB);

    Entity player1B = ecs.spawn_entity();
    ecs.add_component<Position>(player1B,
                                {float(serverSize.x) / 12 * float(6.14),
                                 float(serverSize.y) / 10 * float(3.9)});
    ecs.add_component<Tag>(player1B, {});
    ecs.add_component<Scene>(player1B, {M_CONFIG});
    ecs.add_component<Hitbox>(player1B, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 1")});
    texts.insert({"FR", std::make_shared<std::string>("Joueur 1")});
    ecs.add_component<Text>(player1B, {texts,
                                       SFMLObj._font,
                                       {0.5, 0.5},
                                       0,
                                       40,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player1B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player1B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player1B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({M_C_GENERAL});
                       ecs.post<DeleteEvent>({M_C_PLAYER2});
                       ecs.post<CreationEvent>({M_C_PLAYER1});
                   },
                   1});

    Entity player2B = ecs.spawn_entity();
    ecs.add_component<Position>(player2B,
                                {float(serverSize.x) / 12 * float(5.17),
                                 float(serverSize.y) / 10 * float(5.2)});
    ecs.add_component<Tag>(player2B, {});
    ecs.add_component<Scene>(player2B, {M_CONFIG});
    ecs.add_component<Hitbox>(player2B, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Player 2")});
    texts.insert({"FR", std::make_shared<std::string>("Joueur 2")});
    ecs.add_component<Text>(player2B, {texts,
                                       SFMLObj._font,
                                       {0.5, 0.5},
                                       0,
                                       40,
                                       sf::Color::White,
                                       sf::Text::Style::Regular});
    ecs.add_component<Drawable>(player2B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        player2B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_sel.png"),
                   std::function<void(ECS &, Entity)>(select),
                   std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        player2B, {SFMLObj._myTextures.getTexture(
                       "assets/images/utils/button_config1_act.png"),
                   [](ECS &ecs, Entity i) {
                       press(ecs, i);
                       ecs.post<DeleteEvent>({M_C_GENERAL});
                       ecs.post<DeleteEvent>({M_C_PLAYER1});
                       ecs.post<CreationEvent>({M_C_PLAYER2});
                   },
                   1});

    Entity backB = ecs.spawn_entity();
    ecs.add_component<Position>(backB, {float(serverSize.x) / 12 * float(4.2),
                                        float(serverSize.y) / 10 * float(6.5)});
    ecs.add_component<Tag>(backB, {});
    ecs.add_component<Scene>(backB, {M_CONFIG});
    ecs.add_component<Hitbox>(backB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Back")});
    texts.insert({"FR", std::make_shared<std::string>("Retour")});
    ecs.add_component<Text>(backB, {texts,
                                    SFMLObj._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(backB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        backB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        backB, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                    ecs.post<DeleteEvent>({M_CONFIG});
                    ecs.post<DeleteEvent>({M_C_GENERAL});
                    ecs.post<DeleteEvent>({M_C_PLAYER1});
                    ecs.post<DeleteEvent>({M_C_PLAYER2});
                    ecs.post<CreationEvent>({M_GENERAL});
                }});
}

void createConfigGeneralEntites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {});
    ecs.add_component<Scene>(title, {M_C_GENERAL});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("General")});
    texts.insert({"FR", std::make_shared<std::string>("General")});
    ecs.add_component<Text>(
        title, {texts, SFMLObj._font, {1, 1}, 0, 30, sf::Color::White});

    Entity interactP = ecs.spawn_entity();
    ecs.add_component<Position>(interactP,
                                {float(serverSize.x) / 8 * float(5.5),
                                 float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Tag>(interactP, {});
    ecs.add_component<Scene>(interactP, {M_C_GENERAL});
    ecs.add_component<Hitbox>(interactP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Interact")});
    texts.insert({"FR", std::make_shared<std::string>("Interagir")});
    ecs.add_component<Text>(interactP, {texts,
                                        SFMLObj._font,
                                        {1, 1},
                                        -0.1,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});

    Entity colorP = ecs.spawn_entity();
    ecs.add_component<Position>(colorP,
                                {float(serverSize.x) / 8 * float(5.5),
                                 float(serverSize.y) / 15 * float(7.6)});
    ecs.add_component<Tag>(colorP, {});
    ecs.add_component<Scene>(colorP, {M_C_GENERAL});
    ecs.add_component<Hitbox>(colorP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Colorblind mode")});
    texts.insert({"FR", std::make_shared<std::string>("Mode daltonien")});
    ecs.add_component<Text>(colorP, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity languageP = ecs.spawn_entity();
    ecs.add_component<Position>(languageP,
                                {float(serverSize.x) / 8 * float(5.1),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(languageP, {});
    ecs.add_component<Scene>(languageP, {M_C_GENERAL});
    ecs.add_component<Hitbox>(languageP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Language")});
    texts.insert({"FR", std::make_shared<std::string>("Langue")});
    ecs.add_component<Text>(languageP, {texts,
                                        SFMLObj._font,
                                        {1, 1},
                                        -0.1,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});

    Entity resP = ecs.spawn_entity();
    ecs.add_component<Position>(resP, {float(serverSize.x) / 8 * float(4.3),
                                       float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(resP, {});
    ecs.add_component<Scene>(resP, {M_C_GENERAL});
    ecs.add_component<Hitbox>(resP, {{float(1) / 4, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Window resolution")});
    texts.insert({"FR", std::make_shared<std::string>("taille de la fenetre")});
    ecs.add_component<Text>(resP, {texts,
                                   SFMLObj._font,
                                   {1, 1},
                                   -0.1,
                                   30,
                                   sf::Color::White,
                                   sf::Text::Style::Regular});

    Entity interactB = ecs.spawn_entity();
    ecs.add_component<Position>(
        interactB,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Tag>(interactB, {});
    ecs.add_component<Scene>(interactB, {M_C_GENERAL});
    ecs.add_component<Hitbox>(interactB, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(ENTER)->second.second});
    ecs.add_component<Text>(interactB, {texts,
                                        SFMLObj._font,
                                        {1, 1},
                                        0,
                                        30,
                                        sf::Color::White,
                                        sf::Text::Style::Regular});
    ecs.add_component<Drawable>(interactB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        interactB, {SFMLObj._myTextures.getTexture(
                        "assets/images/utils/button_config2_sel.png"),
                    std::function<void(ECS &, Entity)>(select),
                    std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        interactB,
        {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(colorB, {});
    ecs.add_component<Scene>(colorB, {M_C_GENERAL});
    ecs.add_component<Hitbox>(colorB, {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Drawable>(colorB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/toggle_config.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        colorB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/toggle_config_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        colorB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/toggle_config_act.png"),
                 std::function<void(ECS &, Entity)>(swapColorblind)});
    if (myConfig._colorblind)
        press(ecs, colorB);

    Entity res1B = ecs.spawn_entity();
    ecs.add_component<Position>(res1B,
                                {float(serverSize.x) / 8 * float(7.3),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res1B, {});
    ecs.add_component<Scene>(res1B, {M_C_GENERAL});
    ecs.add_component<Hitbox>(res1B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("1920 x 1080")});
    ecs.add_component<Text>(res1B, {texts,
                                    SFMLObj._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res1B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res1B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res1B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize1920), 2});
    if (myConfig._size.x == 1920)
        press(ecs, res1B);

    Entity res2B = ecs.spawn_entity();
    ecs.add_component<Position>(res2B,
                                {float(serverSize.x) / 8 * float(6.5),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res2B, {});
    ecs.add_component<Scene>(res2B, {M_C_GENERAL});
    ecs.add_component<Hitbox>(res2B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("1440 x 810")});
    ecs.add_component<Text>(res2B, {texts,
                                    SFMLObj._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res2B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res2B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res2B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize1440), 2});
    if (myConfig._size.x == 1440)
        press(ecs, res2B);

    Entity res3B = ecs.spawn_entity();
    ecs.add_component<Position>(res3B,
                                {float(serverSize.x) / 8 * float(5.7),
                                 float(serverSize.y) / 15 * float(11.8)});
    ecs.add_component<Tag>(res3B, {});
    ecs.add_component<Scene>(res3B, {M_C_GENERAL});
    ecs.add_component<Hitbox>(res3B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("960 x 540")});
    ecs.add_component<Text>(res3B, {texts,
                                    SFMLObj._font,
                                    {1, 1},
                                    0,
                                    20,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
    ecs.add_component<Drawable>(res3B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        res3B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        res3B, {SFMLObj._myTextures.getTexture(
                    "assets/images/utils/button_config2_act.png"),
                std::function<void(ECS &, Entity)>(resize960), 2});
    if (myConfig._size.x == 960)
        press(ecs, res3B);

    Entity lang1B = ecs.spawn_entity();
    ecs.add_component<Position>(lang1B,
                                {float(serverSize.x) / 8 * float(7.3),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(lang1B, {});
    ecs.add_component<Scene>(lang1B, {M_C_GENERAL});
    ecs.add_component<Hitbox>(lang1B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("FR")});
    ecs.add_component<Text>(lang1B, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     0,
                                     20,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(lang1B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        lang1B, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config2_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        lang1B, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config2_act.png"),
                 std::function<void(ECS &, Entity)>(langFR), 3});
    if (myConfig._lang == "FR")
        press(ecs, lang1B);

    Entity lang2B = ecs.spawn_entity();
    ecs.add_component<Position>(lang2B,
                                {float(serverSize.x) / 8 * float(6.5),
                                 float(serverSize.y) / 15 * float(9.7)});
    ecs.add_component<Tag>(lang2B, {});
    ecs.add_component<Scene>(lang2B, {M_C_GENERAL});
    ecs.add_component<Hitbox>(lang2B, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert({"DEFAULT", std::make_shared<std::string>("EN")});
    ecs.add_component<Text>(lang2B, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     0,
                                     20,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(lang2B,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        lang2B, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config2_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        lang2B, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config2_act.png"),
                 std::function<void(ECS &, Entity)>(langEN), 3});
    if (myConfig._lang == "EN")
        press(ecs, lang2B);

    Entity resetB = ecs.spawn_entity();
    ecs.add_component<Position>(resetB,
                                {float(serverSize.x) / 12 * float(2.95),
                                 float(serverSize.y) / 10 * float(8.2)});
    ecs.add_component<Tag>(resetB, {});
    ecs.add_component<Scene>(resetB, {M_C_GENERAL});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     SFMLObj._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetG)});
}

void createConfigPlayer1Entites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {});
    ecs.add_component<Scene>(title, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("Keyboard")});
    texts.insert({"FR", std::make_shared<std::string>("Clavier")});
    ecs.add_component<Text>(
        title, {texts, SFMLObj._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param1,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(param1, {});
    ecs.add_component<Scene>(param1, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param1, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Top")});
    texts.insert({"FR", std::make_shared<std::string>("Haut")});
    ecs.add_component<Text>(param1, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Position>(param2, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(param2, {});
    ecs.add_component<Scene>(param2, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param2, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Down")});
    texts.insert({"FR", std::make_shared<std::string>("Bas")});
    ecs.add_component<Text>(param2, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param3,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(param3, {});
    ecs.add_component<Scene>(param3, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param3, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Left")});
    texts.insert({"FR", std::make_shared<std::string>("Gauche")});
    ecs.add_component<Text>(param3, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Position>(param4, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(param4, {});
    ecs.add_component<Scene>(param4, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param4, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Right")});
    texts.insert({"FR", std::make_shared<std::string>("Droite")});
    ecs.add_component<Text>(param4, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param5,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(param5, {});
    ecs.add_component<Scene>(param5, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param5, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Tir")});
    ecs.add_component<Text>(param5, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Position>(param6, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(param6, {});
    ecs.add_component<Scene>(param6, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(param6, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Super shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Super tir")});
    ecs.add_component<Text>(param6, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(button1, {});
    ecs.add_component<Scene>(button1, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(UP1P)->second.second});
    ecs.add_component<Text>(button1, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button1,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button1, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button1, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({UP1P, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Position>(button2, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(button2, {});
    ecs.add_component<Scene>(button2, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button2, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(DOWN1P)->second.second});
    ecs.add_component<Text>(button2, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button2,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button2, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button2, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button3, {});
    ecs.add_component<Scene>(button3, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button3, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(LEFT1P)->second.second});
    ecs.add_component<Text>(button3, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button3,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button3, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button3, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({LEFT1P, i});
                  }});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Position>(button4, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(button4, {});
    ecs.add_component<Scene>(button4, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button4, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(RIGHT1P)->second.second});
    ecs.add_component<Text>(button4, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button4,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button4, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button4, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button5, {});
    ecs.add_component<Scene>(button5, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button5, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(SHOOT1)->second.second});
    ecs.add_component<Text>(button5, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button5,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button5, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button5, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button6, {});
    ecs.add_component<Scene>(button6, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(button6, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT",
         myConfig._inputConfig.first.find(SUPERSHOOT1)->second.second});
    ecs.add_component<Text>(button6, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button6,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button6, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button6, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(resetB, {});
    ecs.add_component<Scene>(resetB, {M_C_PLAYER1});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     SFMLObj._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetP1)});
}

void createConfigPlayer2Entites(ECS &ecs, const Configs &myConfig,
                                SFMLObjects &SFMLObj) {
    auto serverSize = myConfig._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Tag>(title, {});
    ecs.add_component<Scene>(title, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(title, {{float(1) / 4, float(1) / 15}});
    std::map<std::string, std::shared_ptr<std::string>> texts;
    texts.insert({"EN", std::make_shared<std::string>("Keyboard")});
    texts.insert({"FR", std::make_shared<std::string>("Clavier")});
    ecs.add_component<Text>(
        title, {texts, SFMLObj._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param1,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(param1, {});
    ecs.add_component<Scene>(param1, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param1, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Top")});
    texts.insert({"FR", std::make_shared<std::string>("Haut")});
    ecs.add_component<Text>(param1, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Position>(param2, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(param2, {});
    ecs.add_component<Scene>(param2, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param2, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Down")});
    texts.insert({"FR", std::make_shared<std::string>("Bas")});
    ecs.add_component<Text>(param2, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param3,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Tag>(param3, {});
    ecs.add_component<Scene>(param3, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param3, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Left")});
    texts.insert({"FR", std::make_shared<std::string>("Gauche")});
    ecs.add_component<Text>(param3, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Position>(param4, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(param4, {});
    ecs.add_component<Scene>(param4, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param4, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Right")});
    texts.insert({"FR", std::make_shared<std::string>("Droite")});
    ecs.add_component<Text>(param4, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Position>(
        param5,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Tag>(param5, {});
    ecs.add_component<Scene>(param5, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param5, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Tir")});
    ecs.add_component<Text>(param5, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Position>(param6, {float(serverSize.x) / 8 * 6,
                                         float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Tag>(param6, {});
    ecs.add_component<Scene>(param6, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(param6, {{float(1) / 8, float(1) / 15}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Super shoot")});
    texts.insert({"FR", std::make_shared<std::string>("Super tir")});
    ecs.add_component<Text>(param6, {texts,
                                     SFMLObj._font,
                                     {1, 1},
                                     -0.1,
                                     30,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Tag>(button1, {});
    ecs.add_component<Scene>(button1, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(UP2P)->second.second});
    ecs.add_component<Text>(button1, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button1,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button1, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button1, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({UP2P, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Position>(button2, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Tag>(button2, {});
    ecs.add_component<Scene>(button2, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button2, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(DOWN2P)->second.second});
    ecs.add_component<Text>(button2, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button2,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button2, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button2, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button3, {});
    ecs.add_component<Scene>(button3, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button3, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(LEFT2P)->second.second});
    ecs.add_component<Text>(button3, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button3,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button3, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button3, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_act.png"),
                  [](ECS &ecs, Entity i) {
                      press(ecs, i);
                      ecs.post<FrameEvent>({std::chrono::steady_clock::now()});
                      ecs.post<ChangeKey>({LEFT2P, i});
                  }});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Position>(button4, {float(serverSize.x) / 8 * 7,
                                          float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Tag>(button4, {});
    ecs.add_component<Scene>(button4, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button4, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(RIGHT2P)->second.second});
    ecs.add_component<Text>(button4, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button4,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button4, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button4, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button5, {});
    ecs.add_component<Scene>(button5, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button5, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", myConfig._inputConfig.first.find(SHOOT2)->second.second});
    ecs.add_component<Text>(button5, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button5,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button5, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button5, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(button6, {});
    ecs.add_component<Scene>(button6, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(button6, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT",
         myConfig._inputConfig.first.find(SUPERSHOOT2)->second.second});
    ecs.add_component<Text>(button6, {texts,
                                      SFMLObj._font,
                                      {1, 1},
                                      0,
                                      30,
                                      sf::Color::White,
                                      sf::Text::Style::Regular});
    ecs.add_component<Drawable>(button6,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config2.png"),
                                 {128, 64},
                                 {128, 64},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        button6, {SFMLObj._myTextures.getTexture(
                      "assets/images/utils/button_config2_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button6, {SFMLObj._myTextures.getTexture(
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
    ecs.add_component<Tag>(resetB, {});
    ecs.add_component<Scene>(resetB, {M_C_PLAYER2});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Reset")});
    texts.insert({"FR", std::make_shared<std::string>("Reinitialiser")});
    ecs.add_component<Text>(resetB, {texts,
                                     SFMLObj._font,
                                     {0.5, 0.5},
                                     0,
                                     40,
                                     sf::Color::White,
                                     sf::Text::Style::Regular});
    ecs.add_component<Drawable>(resetB,
                                {SFMLObj._myTextures.getTexture(
                                     "assets/images/utils/button_config1.png"),
                                 {402, 100},
                                 {402, 100},
                                 1,
                                 2});
    ecs.add_component<Selectable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_sel.png"),
                 std::function<void(ECS &, Entity)>(select),
                 std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        resetB, {SFMLObj._myTextures.getTexture(
                     "assets/images/utils/button_config1_act.png"),
                 std::function<void(ECS &, Entity)>(resetP2)});
}

} // namespace rtype::client
