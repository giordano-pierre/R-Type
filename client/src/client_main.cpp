/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_main
*/
#include <iostream>

#include "ECS/ECS.hpp"
#include "createEntities.hpp"
#include "ecsObjects.hpp"
#include "loadSystems.hpp"
#include "tools.hpp"

int main(void) {
  // int mainTestGame (void) {
  Rtype::Client::TupleUInt serverSize = {1920, 1080};
  ECS ecs;

  ecs.register_component<Rtype::Client::Window>();
  ecs.register_component<Rtype::Client::Tag>();
  ecs.register_component<Rtype::Client::Position>();
  ecs.register_component<Rtype::Client::Velocity>();
  ecs.register_component<Rtype::Client::Drawable>();
  ecs.register_component<Rtype::Client::Playable>();
  ecs.register_component<Rtype::Client::Hitbox>();
  ecs.register_component<Rtype::Client::Selectable>();
  ecs.register_component<Rtype::Client::Text>();
  ecs.register_component<Rtype::Client::Pressable>();

  ecs.register_event<Rtype::Client::FrameEvent>();
  ecs.register_event<Rtype::Client::InputEvent>();
  ecs.register_event<Rtype::Client::TicEvent>();
  ecs.register_event<Rtype::Client::ChangeKey>();

  Entity window = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Tag>(window, {Rtype::Client::WINDOW});
  ecs.add_component<Rtype::Client::Window>(
      window, {"assets/font/retro_gaming.ttf", {1280, 720}, serverSize});

  auto windowSys = Rtype::Client::WindowSys(
      {1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
  ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window,
                Rtype::Client::Position, Rtype::Client::Hitbox,
                Rtype::Client::Drawable, Rtype::Client::Text,
                Rtype::Client::Selectable>(windowSys);
  ecs.subscribe<Rtype::Client::ChangeKey, Rtype::Client::Window>(windowSys);

  auto cheatSys = Rtype::Client::CheatSys();
  ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys);

  bool running = true;
  ecs.subscribe<Rtype::Client::InputEvent>(
      [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
        if (e_input._myEvent == Rtype::Client::QUIT ||
            e_input._event.type == sf::Event::Closed) {
          running = false;
        }
      });

  Rtype::Client::createGameEntities(ecs);
  Rtype::Client::loadGameSystem(ecs);
  // Rtype::Client::createMenuEntities(ecs);
  //   Rtype::Client::createConfigEntities(ecs);
  // Rtype::Client::loadMenuSystem(ecs);

  const auto FPS = 60;
  const timer::duration<double, std::ratio<1, FPS>> frameRate(1);
  timer::time_point<timer::steady_clock> frameStart;
  timer::time_point<timer::steady_clock> newTime;
  timer::duration<double> dtime = timer::duration<double>::zero();

  while (running) {
    newTime = timer::steady_clock::now();
    dtime += newTime - frameStart;
    frameStart = newTime;

    if (dtime >= frameRate) {
      ecs.post<Rtype::Client::TicEvent>({std::chrono::steady_clock::now()});
      ecs.post<Rtype::Client::FrameEvent>({std::chrono::steady_clock::now()});

      while (!ecs.empty()) {
        auto evt = ecs.front();
        evt();
        ecs.pop_front();
      }
      dtime = std::chrono::duration<double>::zero();
    }
  }
  return 0;
}
