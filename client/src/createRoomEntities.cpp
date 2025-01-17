/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** createEntities
*/
#include "RequestEvent.hpp"
#include "buttonFunctions.hpp"
#include "createEntities.hpp"
#include "ecsObjects.hpp"
#include <iostream>

namespace rtype::client {
void createMenuRoomEntities(ECS &ecs) {
    auto myWindow = ecs.get_components<Window>()[0].value();
    auto serverSize = myWindow._serverSize;

    std::map<std::string, std::shared_ptr<std::string>> texts;

    // background
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

    // the input button
    Entity button1 = ecs.spawn_entity();
    ecs.add_component<Position>(
        button1, {float(serverSize.x) / 2, float(serverSize.y) / 2});
    ecs.add_component<Tag>(button1, {CPLAYER1});
    ecs.add_component<Hitbox>(button1, {{float(1) / 10, float(1) / 10}});
    texts.clear();
    texts.insert(
        {"DEFAULT", std::make_shared<std::string>("Enter Room Number:")});
    // texts.insert({"EN", std::make_shared<std::string>("")});
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
                      auto textOpt = ecs.get_components<Text>()[i];
                      if (textOpt.has_value()) {
                          auto &text = *textOpt;
                          if (text._str["DEFAULT"]) {
                              text._str["DEFAULT"]->clear();
                          }
                      }
                      press(ecs, i);
                      ecs.post<CaptureInputEvent>({i});
                  }});

    // title
    Entity title = ecs.spawn_entity();
    ecs.add_component<Position>(
        title, {float(serverSize.x) / 2, float(serverSize.y) / 6});
    texts.clear();
    texts.insert({"EN", std::make_shared<std::string>("Menu Lobby")});
    texts.insert({"FR", std::make_shared<std::string>("Menu Lobby")});
    ecs.add_component<Text>(title, {texts,
                                    myWindow._font,
                                    {100, 100},
                                    1,
                                    50,
                                    sf::Color::White,
                                    sf::Text::Style::Bold});
    // ecs.add_component<Drawable>(title,
    // );
}
} // namespace rtype::client
