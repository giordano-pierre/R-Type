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
    rtype::client::TupleUInt serverSize = {1920, 1080};
    ECS ecs;

    ecs.register_component<rtype::client::Window>();
    ecs.register_component<rtype::client::Tag>();
    ecs.register_component<rtype::client::Position>();
    ecs.register_component<rtype::client::Velocity>();
    ecs.register_component<rtype::client::Drawable>();
    ecs.register_component<rtype::client::Playable>();
    ecs.register_component<rtype::client::Hitbox>();
    ecs.register_component<rtype::client::Selectable>();
    ecs.register_component<rtype::client::Text>();
    ecs.register_component<rtype::client::Pressable>();

    ecs.register_event<rtype::client::FrameEvent>();
    ecs.register_event<rtype::client::InputEvent>();
    ecs.register_event<rtype::client::TicEvent>();
    ecs.register_event<rtype::client::ChangeKey>();
    ecs.register_event<rtype::client::CreationEvent>();
    ecs.register_event<rtype::client::DeleteEvent>();
    ecs.register_event<rtype::client::AnimeEvent>();
    ecs.register_event<RequestEvent>();
    ecs.register_event<ReceiveEvent>();

    UDPClient client(ecs, "127.0.0.1", "4242");
    ecs.subscribe<RequestEvent>(client, true);

    ClientHandlerSystem client_handler;
    ecs.subscribe<ReceiveEvent>(client_handler, true);

    ecs.post<RequestEvent>({NetworkActions::CONNECT, {"action", "connect"}});

    Entity window = ecs.spawn_entity();
    ecs.add_component<rtype::client::Tag>(window, {rtype::client::WINDOW});
    ecs.add_component<rtype::client::Window>(
        window, {"assets/font/retro_gaming.ttf", {1440, 810}, serverSize});

    auto lifeSys = rtype::client::LifeSys();
    ecs.subscribe<rtype::client::CreationEvent>(lifeSys, true);
    ecs.subscribe<rtype::client::DeleteEvent, rtype::client::Tag>(lifeSys,
                                                                  true);

    auto windowSys = rtype::client::WindowSys(
        {1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<rtype::client::FrameEvent, rtype::client::Window,
                  rtype::client::Position, rtype::client::Hitbox,
                  rtype::client::Drawable, rtype::client::Text,
                  rtype::client::Selectable>(windowSys, true);
    ecs.subscribe<rtype::client::ChangeKey, rtype::client::Window>(windowSys,
                                                                   true);

    auto cheatSys = rtype::client::CheatSys();
    ecs.subscribe<rtype::client::InputEvent, rtype::client::Window>(cheatSys,
                                                                    true);

    auto frameSys = rtype::client::FrameSys();
    ecs.subscribe<rtype::client::AnimeEvent, rtype::client::Drawable>(frameSys,
                                                                      true);

    bool running = true;
    ecs.subscribe<rtype::client::InputEvent>(
        [&running](ECS &ecs, const rtype::client::InputEvent &e_input) -> void {
            if (e_input._myEvent == rtype::client::QUIT ||
                e_input._event.type == sf::Event::Closed) {
                running = false;
                ecs.post<RequestEvent>({CLIENT_DISCONNECT, {}});
            }
        },
        true);

    ecs.post<rtype::client::CreationEvent>({rtype::client::MENU});

    const auto FPS = 60;
    const timer::duration<double, std::ratio<1, FPS>> frameRate(1);
    timer::time_point<timer::steady_clock> frameStart;
    timer::duration<double> dtimeF = timer::duration<double>::zero();

    const auto Animation = 25;
    const timer::duration<double, std::ratio<1, Animation>> animeRate(1);
    timer::time_point<timer::steady_clock> animeStart;
    timer::duration<double> dtimeA = timer::duration<double>::zero();

    timer::time_point<timer::steady_clock> newTime;

    while (running) {
        bool trigger = false;
        newTime = timer::steady_clock::now();
        dtimeF += newTime - frameStart;
        frameStart = newTime;
        dtimeA += newTime - animeStart;
        animeStart = newTime;

        if (dtimeF >= frameRate) {
            ecs.post<rtype::client::TicEvent>(
                {std::chrono::steady_clock::now()});
            ecs.post<rtype::client::FrameEvent>(
                {std::chrono::steady_clock::now()});
            dtimeF = std::chrono::duration<double>::zero();
            trigger = true;
        }

        if (dtimeA >= animeRate) {
            ecs.post<rtype::client::AnimeEvent>(
                {std::chrono::steady_clock::now()});
            dtimeA = std::chrono::duration<double>::zero();
            trigger = true;
        }
        if (trigger) {
            while (!ecs.empty()) {
                auto evt = ecs.front();
                evt();
                ecs.pop_front();
            }
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
