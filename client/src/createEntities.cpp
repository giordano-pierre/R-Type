/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/
#include "buttonFunctions.hpp"
#include "createEntities.hpp"
#include "ecsObjects.hpp"
#include <iostream>

namespace Rtype::Client {

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
                                        1});
}

void createMenuEntities(ECS &ecs) {
  auto myWindow = ecs.get_components<Window>()[0].value();
  auto serverSize = myWindow._serverSize;

  Entity back1 = ecs.spawn_entity();
  ecs.add_component<Position>(
      back1, {serverSize.x / float(2), serverSize.y / float(2)});
  ecs.add_component<Tag>(back1, {MENU});
  ecs.add_component<Hitbox>(back1, {{1, 1}, false});
  ecs.add_component<Drawable>(
      back1, {myWindow._myTextures.getTexture(
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
                               1});
  ecs.add_component<Selectable>(
      startB, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config1_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      startB, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config1_act.png"),
               [](ECS &ecs, Entity) {ecs.post<DeleteEvent>({MENU}); ecs.post<CreateEvent>({PLAYER});}
              });

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
                  ecs.post<CreateEvent>({CONFIG});
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

void createConfigEntities(ECS &ecs) {
  auto myWindow = ecs.get_components<Window>()[0].value();
  auto serverSize = myWindow._serverSize;

  Entity back1 = ecs.spawn_entity();
  ecs.add_component<Position>(
      back1, {serverSize.x / float(2), serverSize.y / float(2)});
  ecs.add_component<Tag>(back1, {MENU});
  ecs.add_component<Hitbox>(back1, {{1, 1}, false});
  ecs.add_component<Drawable>(
      back1, {myWindow._myTextures.getTexture(
                  "assets/images/background/back_menu.jpg"),
              {4608, 3456},
              {768, 432},
              48});
  Entity back2 = ecs.spawn_entity();
  ecs.add_component<Position>(
      back2, {serverSize.x / float(2), serverSize.y * float(0.9) / float(2)});
  ecs.add_component<Tag>(back2, {MENU});
  ecs.add_component<Hitbox>(back2, {{1, 0.9}, false});
  ecs.add_component<Drawable>(
      back2, {myWindow._myTextures.getTexture(
                  "assets/images/background/back_config.png"),
              {512, 288},
              {512, 288},
              1});


  Entity buttonM1 = ecs.spawn_entity();
  ecs.add_component<Position>(
      buttonM1, {float(serverSize.x) / 12 * float(7.11), float(serverSize.y) / 10 * float(2.6)});
  ecs.add_component<Tag>(buttonM1, {CONFIG});
  ecs.add_component<Hitbox>(buttonM1, {{float(1) / 4, float(1) / 10}});
  ecs.add_component<Text>(
      buttonM1, {"General", myWindow._font, {0.5, 0.5}, 0, 40, sf::Color::White});
  ecs.add_component<Drawable>(buttonM1,
                              {myWindow._myTextures.getTexture(
                                   "assets/images/utils/button_config1.png"),
                               {402, 100},
                               {402, 100},
                               1});
  ecs.add_component<Selectable>(
      buttonM1, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config1_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      buttonM1, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config1_act.png"),
               [](ECS &ecs, Entity i) {
                 std::cout << "Draw general configs" << std::endl;
               }});

  Entity buttonM2 = ecs.spawn_entity();
  ecs.add_component<Position>(
      buttonM2, {float(serverSize.x) / 12 * float(6.14), float(serverSize.y) / 10 * float(3.9)});
  ecs.add_component<Tag>(buttonM2, {MENU});
  ecs.add_component<Hitbox>(buttonM2, {{float(1) / 4, float(1) / 10}});
  ecs.add_component<Text>(buttonM2, {"Player 1",
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
  ecs.add_component<Drawable>(buttonM2,
                              {myWindow._myTextures.getTexture(
                                   "assets/images/utils/button_config1.png"),
                               {402, 100},
                               {402, 100},
                               1});
  ecs.add_component<Selectable>(
      buttonM2, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      buttonM2, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                  std::cout << "Draw plyer 1 config" << std::endl;
                }});

  Entity buttonM3 = ecs.spawn_entity();
  ecs.add_component<Position>(
      buttonM3, {float(serverSize.x) / 12 * float(5.17), float(serverSize.y) / 10 * float(5.2)});
  ecs.add_component<Tag>(buttonM3, {MENU});
  ecs.add_component<Hitbox>(buttonM3, {{float(1) / 4, float(1) / 10}});
  ecs.add_component<Text>(buttonM3, {"Player 2",
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
  ecs.add_component<Drawable>(buttonM3,
                              {myWindow._myTextures.getTexture(
                                   "assets/images/utils/button_config1.png"),
                               {402, 100},
                               {402, 100},
                               1});
  ecs.add_component<Selectable>(
      buttonM3, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      buttonM3, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_act.png"),
                [](ECS &ecs, Entity) {
                  std::cout << "Draw player 2 configs" << std::endl;
                }});

  Entity buttonM4 = ecs.spawn_entity();
  ecs.add_component<Position>(
      buttonM4, {float(serverSize.x) / 12 * float(4.2), float(serverSize.y) / 10 * float(6.5)});
  ecs.add_component<Tag>(buttonM4, {MENU});
  ecs.add_component<Hitbox>(buttonM4, {{float(1) / 4, float(1) / 10}});
  ecs.add_component<Text>(buttonM4, {"Back",
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
  ecs.add_component<Drawable>(buttonM4,
                              {myWindow._myTextures.getTexture(
                                   "assets/images/utils/button_config1.png"),
                               {402, 100},
                               {402, 100},
                               1});
  ecs.add_component<Selectable>(
      buttonM4, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      buttonM4,
      {myWindow._myTextures.getTexture(
           "assets/images/utils/button_config1_act.png"),
       [](ECS &ecs, Entity) { std::cout << "go back to menu" << std::endl; }});

  Entity buttonReset = ecs.spawn_entity();
  ecs.add_component<Position>(
      buttonReset, {float(serverSize.x) / 12 * float(2.95), float(serverSize.y) / 10 * float(8.2)});
  ecs.add_component<Tag>(buttonReset, {CONFIG});
  ecs.add_component<Hitbox>(buttonReset, {{float(1) / 4, float(1) / 10}});
  ecs.add_component<Text>(buttonReset, {"Reset",
                                    myWindow._font,
                                    {0.5, 0.5},
                                    0,
                                    40,
                                    sf::Color::White,
                                    sf::Text::Style::Regular});
  ecs.add_component<Drawable>(buttonReset,
                              {myWindow._myTextures.getTexture(
                                   "assets/images/utils/button_config1.png"),
                               {402, 100},
                               {402, 100},
                               1});
  ecs.add_component<Selectable>(
      buttonReset, {myWindow._myTextures.getTexture(
                    "assets/images/utils/button_config1_sel.png"),
                std::function<void(ECS &, Entity)>(select),
                std::function<void(ECS &, Entity)>(deselect)});
  ecs.add_component<Pressable>(
      buttonReset,
      {myWindow._myTextures.getTexture(
           "assets/images/utils/button_config1_act.png"),
       [](ECS &ecs, Entity) { std::cout << "reset configs" << std::endl; }});
}

void createConfigPlayer1Entites(ECS &ecs)
{
  auto myWindow = ecs.get_components<Window>()[0].value();
  auto serverSize = myWindow._serverSize;

  Entity title = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      title, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * 3});
  ecs.add_component<Rtype::Client::Tag>(title, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(title, {{float(1) / 4, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(title, {"Keyboard",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White});

  Entity param1 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param1, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(4.5)});
  ecs.add_component<Rtype::Client::Tag>(param1, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param1, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param1, {"Top",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity param2 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param2, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(6)});
  ecs.add_component<Rtype::Client::Tag>(param2, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param2, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param2, {"Down",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity param3 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param3, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(7.5)});
  ecs.add_component<Rtype::Client::Tag>(param3, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param3, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param3, {"Left",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity param4 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param4, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(9)});
  ecs.add_component<Rtype::Client::Tag>(param4, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param4, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param4, {"Right",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity param5 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param5, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(10.5)});
  ecs.add_component<Rtype::Client::Tag>(param5, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param5, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param5, {"Shoot",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity param6 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      param6, {float(serverSize.x) / 8 * 6, float(serverSize.y) / 15 * float(12)});
  ecs.add_component<Rtype::Client::Tag>(param6, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(param6, {{float(1) / 8, float(1) / 15}});
  ecs.add_component<Rtype::Client::Text>(param6, {"Supershoot",
                                                  myWindow._font,
                                                  {1, 1},
                                                  -0.1,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});

  Entity button1 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button1, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(4.5)});
  ecs.add_component<Rtype::Client::Tag>(button1, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button1, {"Up",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button1,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button1, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});


  Entity button2 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button2, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(6)});
  ecs.add_component<Rtype::Client::Tag>(button2, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button2, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button2, {"Down",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button2,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button2, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});

  Entity button3 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button3, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(7.5)});
  ecs.add_component<Rtype::Client::Tag>(button3, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button3, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button3, {"Left",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button3,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button3, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});

  Entity button4 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button4, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(9)});
  ecs.add_component<Rtype::Client::Tag>(button4, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button4, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button4, {"Right",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button4,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button4, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});

  Entity button5 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button5, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(10.5)});
  ecs.add_component<Rtype::Client::Tag>(button5, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button5, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button5, {"Space",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button5,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button5, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});

  Entity button6 = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Position>(
      button6, {float(serverSize.x) / 8 * 7, float(serverSize.y) / 15 * float(12)});
  ecs.add_component<Rtype::Client::Tag>(button6, {CPLAYER});
  ecs.add_component<Rtype::Client::Hitbox>(button6, {{float(1) / 10, float(1) / 10}});
  ecs.add_component<Rtype::Client::Text>(button6, {"Enter",
                                                  myWindow._font,
                                                  {1, 1},
                                                  0,
                                                  30,
                                                  sf::Color::White,
                                                  sf::Text::Style::Regular});
  ecs.add_component<Rtype::Client::Drawable>(
      button6,
      {myWindow._myTextures.getTexture("assets/images/utils/button_config2.png"),
       {128, 64},
       {128, 64},
       1});
  ecs.add_component<Selectable>(
      button6, {myWindow._myTextures.getTexture(
                   "assets/images/utils/button_config2_sel.png"),
               std::function<void(ECS &, Entity)>(select),
               std::function<void(ECS &, Entity)>(deselect)});
}

} // namespace Rtype::Client
