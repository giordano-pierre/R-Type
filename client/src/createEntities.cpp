/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/
#include "createEntities.hpp"
#include "buttonFunctions.hpp"
#include "ecsObjects.hpp"
#include <iostream>

namespace Rtype::Client
{

  void createGameEntities(ECS &ecs)
  {
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
    ecs.add_component<Position>(
        back2, {serverSize.x / float(2) + serverSize.x, serverSize.y / float(2)});
    ecs.add_component<Velocity>(back2, {-1, 0});
    ecs.add_component<Tag>(back2, {BACKGROUND});
    ecs.add_component<Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Drawable>(
        back2, {myWindow._myTextures.getTexture(
                    "assets/images/background/background_mountain.jpg"),
                {675, 360},
                {675, 360},
                1});

    Entity player1 = ecs.spawn_entity();
    ecs.add_component<Position>(player1, {float(100), serverSize.y / float(2)});
    ecs.add_component<Velocity>(player1, {0, 0});
    ecs.add_component<Playable>(player1, {1});
    ecs.add_component<Tag>(player1, {PLAYER});
    ecs.add_component<Hitbox>(player1, {{0.1, 0.12}});
    ecs.add_component<Drawable>(player1, {myWindow._myTextures.getTexture(
                                              "assets/images/ship/red_ship.png"),
                                          {395, 250},
                                          {395, 250},
                                          1,
                                          1});
  }

  void createMenuEntities(ECS &ecs)
  {
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
    ecs.add_component<Text>(
        startB, {"START", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
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
                 [](ECS &ecs, Entity)
                 {
                   ecs.post<DeleteEvent>({MENU});
                   ecs.post<CreateEvent>({PLAYER});
                 }});

    Entity customB = ecs.spawn_entity();
    ecs.add_component<Position>(
        customB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 4});
    ecs.add_component<Tag>(customB, {MENU});
    ecs.add_component<Hitbox>(customB, {{float(1) / 3, float(1) / 10}});
    ecs.add_component<Text>(customB, {"CUSTOM",
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
                  [](ECS &ecs, Entity)
                  {
                    std::cout << "Custom your ship!" << std::endl;
                  }});

    Entity configB = ecs.spawn_entity();
    ecs.add_component<Position>(
        configB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 5});
    ecs.add_component<Tag>(configB, {MENU});
    ecs.add_component<Hitbox>(configB, {{float(1) / 3, float(1) / 10}});
    ecs.add_component<Text>(configB, {"CONFIGS",
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
                  [](ECS &ecs, Entity)
                  {
                    ecs.post<DeleteEvent>({MENU});
                    ecs.post<CreateEvent>({CONFIG});
                    ecs.post<CreateEvent>({CGENERAL});
                  }});

    Entity quitB = ecs.spawn_entity();
    ecs.add_component<Position>(
        quitB, {float(serverSize.x) / 5, float(serverSize.y) / 7 * 6});
    ecs.add_component<Tag>(quitB, {MENU});
    ecs.add_component<Hitbox>(quitB, {{float(1) / 3, float(1) / 10}});
    ecs.add_component<Text>(quitB, {"QUIT",
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
         [](ECS &ecs, Entity)
         { ecs.post<InputEvent>({sf::Event(), QUIT}); }});
  }

  void createConfigEntities(ECS &ecs)
  {
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
    ecs.add_component<Drawable>(back2,
                                {myWindow._myTextures.getTexture(
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
    ecs.add_component<Text>(
        generalB,
        {"General", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
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
                   [](ECS &ecs, Entity i)
                   {
                     ecs.post<DeleteEvent>({CPLAYER1});
                     ecs.post<CreateEvent>({CGENERAL});
                   }});

    Entity player1B = ecs.spawn_entity();
    ecs.add_component<Position>(player1B,
                                {float(serverSize.x) / 12 * float(6.14),
                                 float(serverSize.y) / 10 * float(3.9)});
    ecs.add_component<Tag>(player1B, {CONFIG});
    ecs.add_component<Hitbox>(player1B, {{float(1) / 4, float(1) / 10}});
    ecs.add_component<Text>(player1B, {"Player 1",
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
                   [](ECS &ecs, Entity)
                   {
                     ecs.post<DeleteEvent>({CGENERAL});
                     ecs.post<CreateEvent>({CPLAYER1});
                   }});

    Entity player2B = ecs.spawn_entity();
    ecs.add_component<Position>(player2B,
                                {float(serverSize.x) / 12 * float(5.17),
                                 float(serverSize.y) / 10 * float(5.2)});
    ecs.add_component<Tag>(player2B, {CONFIG});
    ecs.add_component<Hitbox>(player2B, {{float(1) / 4, float(1) / 10}});
    ecs.add_component<Text>(player2B, {"Player 2",
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
                   [](ECS &ecs, Entity)
                   {
                     std::cout << "Draw player 2 configs" << std::endl;
                   }});

    Entity backB = ecs.spawn_entity();
    ecs.add_component<Position>(backB, {float(serverSize.x) / 12 * float(4.2),
                                        float(serverSize.y) / 10 * float(6.5)});
    ecs.add_component<Tag>(backB, {CONFIG});
    ecs.add_component<Hitbox>(backB, {{float(1) / 4, float(1) / 10}});
    ecs.add_component<Text>(backB, {"Back",
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
                [](ECS &ecs, Entity)
                {
                  ecs.post<DeleteEvent>({CONFIG});
                  ecs.post<DeleteEvent>({CGENERAL});
                  ecs.post<DeleteEvent>({CPLAYER1});
                  ecs.post<CreateEvent>({MENU});
                }});

    Entity resetB = ecs.spawn_entity();
    ecs.add_component<Position>(resetB, {float(serverSize.x) / 12 * float(2.95),
                                         float(serverSize.y) / 10 * float(8.2)});
    ecs.add_component<Tag>(resetB, {CONFIG});
    ecs.add_component<Hitbox>(resetB, {{float(1) / 4, float(1) / 10}});
    ecs.add_component<Text>(resetB, {"Reset",
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
        resetB,
        {myWindow._myTextures.getTexture(
             "assets/images/utils/button_config1_act.png"),
         [](ECS &ecs, Entity)
         { std::cout << "reset configs" << std::endl; }});
  }

  void createConfigPlayer1Entites(ECS &ecs)
  {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Rtype::Client::Tag>(title, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(title,
                                             {{float(1) / 4, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(
        title, {"Keyboard", myWindow._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param1,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Rtype::Client::Tag>(param1, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param1,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param1, {"Top",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param2,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Rtype::Client::Tag>(param2, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param2,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param2, {"Down",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param3,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Rtype::Client::Tag>(param3, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param3,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param3, {"Left",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param4,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Rtype::Client::Tag>(param4, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param4,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param4, {"Right",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param5,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Rtype::Client::Tag>(param5, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param5,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param5, {"Shoot",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param6,
        {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Rtype::Client::Tag>(param6, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(param6,
                                             {{float(1) / 8, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param6, {"Supershoot",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
    ecs.add_component<Rtype::Client::Tag>(button1, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button1,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button1, {getInput(myWindow._inputConfig.first, UP1P),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button1, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({UP1P, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button2,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(6)});
    ecs.add_component<Rtype::Client::Tag>(button2, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button2,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button2, {getInput(myWindow._inputConfig.first, DOWN1P),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button2, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({DOWN1P, i});
                  }});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button3,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(7.5)});
    ecs.add_component<Rtype::Client::Tag>(button3, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button3,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button3, {getInput(myWindow._inputConfig.first, LEFT1P),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button3, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({LEFT1P, i});
                  }});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button4,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(9)});
    ecs.add_component<Rtype::Client::Tag>(button4, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button4,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button4, {getInput(myWindow._inputConfig.first, RIGHT1P),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button4, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({RIGHT1P, i});
                  }});

    Entity button5 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button5,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(10.5)});
    ecs.add_component<Rtype::Client::Tag>(button5, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button5,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button5, {getInput(myWindow._inputConfig.first, SHOOT1),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button5, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({SHOOT1, i});
                  }});

    Entity button6 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button6,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(12)});
    ecs.add_component<Rtype::Client::Tag>(button6, {CPLAYER1});
    ecs.add_component<Rtype::Client::Hitbox>(button6,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button6, {getInput(myWindow._inputConfig.first, SUPERSHOOT1),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button6, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({SUPERSHOOT1, i});
                  }});
  }

  void createConfigGeneralEntites(ECS &ecs)
  {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    Entity title = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
    ecs.add_component<Rtype::Client::Tag>(title, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(title,
                                             {{float(1) / 4, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(
        title, {"General", myWindow._font, {1, 1}, 0, 30, sf::Color::White});

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param1, {float(serverSize.x) / 8 * float(5.5),
                 float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Rtype::Client::Tag>(param1, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param1,
                                             {{float(1) / 4, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param1, {"Interact",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param2, {float(serverSize.x) / 8 * float(5.5),
                 float(serverSize.y) / 15 * float(8.5)});
    ecs.add_component<Rtype::Client::Tag>(param2, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param2,
                                             {{float(1) / 4, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param2, {"Colorblind mode",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        param3,
        {float(serverSize.x) / 8 * 4, float(serverSize.y) / 15 * float(11.5)});
    ecs.add_component<Rtype::Client::Tag>(param3, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param3,
                                             {{float(1) / 4, float(1) / 15}});
    ecs.add_component<Rtype::Client::Text>(param3, {"Window resolution",
                                                    myWindow._font,
                                                    {1, 1},
                                                    -0.1,
                                                    30,
                                                    sf::Color::White,
                                                    sf::Text::Style::Regular});

    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button1,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(5.5)});
    ecs.add_component<Rtype::Client::Tag>(button1, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(button1,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(
        button1, {getInput(myWindow._inputConfig.first, ENTER),
                  myWindow._font,
                  {1, 1},
                  0,
                  30,
                  sf::Color::White,
                  sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        button1, {myWindow._myTextures.getTexture(
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
                  [](ECS &ecs, Entity i)
                  {
                    press(ecs, i);
                    ecs.post<Rtype::Client::FrameEvent>(
                        {std::chrono::steady_clock::now()});
                    ecs.post<ChangeKey>({ENTER, i});
                  }});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        button2,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(8.5)});
    ecs.add_component<Rtype::Client::Tag>(button2, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(button2,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Drawable>(
        button2,
        {myWindow._myTextures.getTexture("assets/images/utils/toggle_config.png"),
         {128, 64},
         {128, 64},
         1,
         2});
    ecs.add_component<Selectable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/toggle_config_sel.png"),
                  std::function<void(ECS &, Entity)>(select),
                  std::function<void(ECS &, Entity)>(deselect)});
    ecs.add_component<Pressable>(
        button2, {myWindow._myTextures.getTexture(
                      "assets/images/utils/toggle_config_act.png"),
                  [](ECS &ecs, Entity i) {}});

    Entity res1B = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        res1B,
        {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(11.5)});
    ecs.add_component<Rtype::Client::Tag>(res1B, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(res1B,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(res1B, {"1920 x 1080",
                                                   myWindow._font,
                                                   {1, 1},
                                                   0,
                                                   20,
                                                   sf::Color::White,
                                                   sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        res1B, {myWindow._myTextures.getTexture(
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
                [](ECS &ecs, Entity i) {

                }});

    Entity res2B = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(
        res2B, {float(serverSize.x) / 8 * float(6),
                float(serverSize.y) / 15 * float(11.5)});
    ecs.add_component<Rtype::Client::Tag>(res2B, {CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(res2B,
                                             {{float(1) / 10, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(res2B, {"1280 x 720",
                                                   myWindow._font,
                                                   {1, 1},
                                                   0,
                                                   20,
                                                   sf::Color::White,
                                                   sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(
        res2B, {myWindow._myTextures.getTexture(
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
                [](ECS &ecs, Entity i) {

                }});

    // Entity button4 = ecs.spawn_entity();
    // ecs.add_component<Rtype::Client::Position>(
    //     button4,
    //     {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(9)});
    // ecs.add_component<Rtype::Client::Tag>(button4, {CPLAYER1});
    // ecs.add_component<Rtype::Client::Hitbox>(button4,
    //                                          {{float(1) / 10, float(1) / 10}});
    // ecs.add_component<Rtype::Client::Text>(button4,
    // {getInput(myWindow._inputConfig.first, RIGHT1P),
    //                                                  myWindow._font,
    //                                                  {1, 1},
    //                                                  0,
    //                                                  30,
    //                                                  sf::Color::White,
    //                                                  sf::Text::Style::Regular});
    // ecs.add_component<Rtype::Client::Drawable>(
    //     button4, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2.png"),
    //               {128, 64},
    //               {128, 64},
    //               1});
    // ecs.add_component<Selectable>(
    //     button4, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2_sel.png"),
    //               std::function<void(ECS &, Entity)>(select),
    //               std::function<void(ECS &, Entity)>(deselect)});
    // ecs.add_component<Pressable>(
    //     button4, {myWindow._myTextures.getTexture(
    //                  "assets/images/utils/button_config2_act.png"),
    //              [](ECS &ecs, Entity i) {
    //                press(ecs, i);
    //                ecs.post<Rtype::Client::FrameEvent>({std::chrono::steady_clock::now()});
    //                ecs.post<ChangeKey>({RIGHT1P, i});
    //              }});

    // Entity button5 = ecs.spawn_entity();
    // ecs.add_component<Rtype::Client::Position>(
    //     button5,
    //     {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(10.5)});
    // ecs.add_component<Rtype::Client::Tag>(button5, {CPLAYER1});
    // ecs.add_component<Rtype::Client::Hitbox>(button5,
    //                                          {{float(1) / 10, float(1) / 10}});
    // ecs.add_component<Rtype::Client::Text>(button5,
    // {getInput(myWindow._inputConfig.first, SHOOT1),
    //                                                  myWindow._font,
    //                                                  {1, 1},
    //                                                  0,
    //                                                  30,
    //                                                  sf::Color::White,
    //                                                  sf::Text::Style::Regular});
    // ecs.add_component<Rtype::Client::Drawable>(
    //     button5, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2.png"),
    //               {128, 64},
    //               {128, 64},
    //               1});
    // ecs.add_component<Selectable>(
    //     button5, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2_sel.png"),
    //               std::function<void(ECS &, Entity)>(select),
    //               std::function<void(ECS &, Entity)>(deselect)});
    // ecs.add_component<Pressable>(
    //     button5, {myWindow._myTextures.getTexture(
    //                  "assets/images/utils/button_config2_act.png"),
    //              [](ECS &ecs, Entity i) {
    //                press(ecs, i);
    //                ecs.post<Rtype::Client::FrameEvent>({std::chrono::steady_clock::now()});
    //                ecs.post<ChangeKey>({SHOOT1, i});
    //              }});

    // Entity button6 = ecs.spawn_entity();
    // ecs.add_component<Rtype::Client::Position>(
    //     button6,
    //     {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(12)});
    // ecs.add_component<Rtype::Client::Tag>(button6, {CPLAYER1});
    // ecs.add_component<Rtype::Client::Hitbox>(button6,
    //                                          {{float(1) / 10, float(1) / 10}});
    // ecs.add_component<Rtype::Client::Text>(button6,
    // {getInput(myWindow._inputConfig.first, SUPERSHOOT1),
    //                                                  myWindow._font,
    //                                                  {1, 1},
    //                                                  0,
    //                                                  30,
    //                                                  sf::Color::White,
    //                                                  sf::Text::Style::Regular});
    // ecs.add_component<Rtype::Client::Drawable>(
    //     button6, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2.png"),
    //               {128, 64},
    //               {128, 64},
    //               1});
    // ecs.add_component<Selectable>(
    //     button6, {myWindow._myTextures.getTexture(
    //                   "assets/images/utils/button_config2_sel.png"),
    //               std::function<void(ECS &, Entity)>(select),
    //               std::function<void(ECS &, Entity)>(deselect)});
    // ecs.add_component<Pressable>(
    //     button6, {myWindow._myTextures.getTexture(
    //                  "assets/images/utils/button_config2_act.png"),
    //              [](ECS &ecs, Entity i) {
    //                press(ecs, i);
    //                ecs.post<Rtype::Client::FrameEvent>({std::chrono::steady_clock::now()});
    //                ecs.post<ChangeKey>({SUPERSHOOT1, i});
    //              }});
  }

} // namespace Rtype::Client
