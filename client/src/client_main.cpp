/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_main
*/
#include <iostream>

#include "ClientHandlerSystem.hpp"
#include "ECS/ECS.hpp"
#include "UDPClient.hpp"
#include "createEntities.hpp"
#include "ecsObjects.hpp"
#include "loadSystems.hpp"
#include "tools.hpp"

int main(void) {
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
  ecs.register_event<Rtype::Client::CreateEvent>();
  ecs.register_event<Rtype::Client::DeleteEvent>();

  Entity window = ecs.spawn_entity();
  ecs.add_component<Rtype::Client::Tag>(window, {Rtype::Client::WINDOW});
  ecs.add_component<Rtype::Client::Window>(
      window, {"assets/font/retro_gaming.ttf", {1280, 720}, serverSize});

  auto lifeSys = Rtype::Client::LifeSys();
  ecs.subscribe<Rtype::Client::CreateEvent>(lifeSys, true);
  ecs.subscribe<Rtype::Client::DeleteEvent, Rtype::Client::Tag>(lifeSys, true);

  auto windowSys = Rtype::Client::WindowSys(
      {1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
  ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window,
                Rtype::Client::Position, Rtype::Client::Hitbox,
                Rtype::Client::Drawable, Rtype::Client::Text,
                Rtype::Client::Selectable>(windowSys, true);
  ecs.subscribe<Rtype::Client::ChangeKey, Rtype::Client::Window>(windowSys,
                                                                 true);

  auto cheatSys = Rtype::Client::CheatSys();
  ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys,
                                                                  true);

  auto frameSys = Rtype::Client::FrameSys();
  ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Drawable>(frameSys,
                                                                    true);

  bool running = true;
  ecs.subscribe<Rtype::Client::InputEvent>(
      [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
        if (e_input._myEvent == Rtype::Client::QUIT ||
            e_input._event.type == sf::Event::Closed) {
          running = false;
        }
      },
      true);

  ecs.post<Rtype::Client::CreateEvent>({Rtype::Client::MENU});

  Rtype::Client::loadMenuSystem(ecs);
  // Rtype::Client::loadGameSystem(ecs);

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

// int main() {
//   // Gui gui("../assets/graphisme/lunar_pirate.gif", 49, 30);
//   // gui.run();

//   try {
//     ECS ecs;
//     ClientHandlerSystem client_handler;
//     UDPClient client(ecs, "127.0.0.1", "4242");
//     ecs.register_event<RequestEvent>();
//     ecs.register_event<ReceiveEvent>();
//     ecs.subscribe<RequestEvent>(client);
//     ecs.subscribe<ReceiveEvent>(client_handler);
//     ecs.post<RequestEvent>({NetworkActions::CONNECT, {"action", "connect"}});
//     while (true) {
//       if (!ecs.empty()) {
//         auto &callback = ecs.front();
//         callback();
//         ecs.pop_front();
//       }
//     };
//     while (true) {
//     };
//   } catch (std::exception &e) {
//     std::cerr << "Error: " << e.what() << std::endl;
//   }
//   return 0;
// }
