/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_main
*/
#include <iostream>

#include "ECS/ECS.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Drawable.hpp"
#include "components/Playable.hpp"
#include "components/Type.hpp"
#include "components/Hitbox.hpp"
#include "components/Window.hpp"

#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"

#include "systems/WindowSys.hpp"
#include "systems/FrameSys.hpp"
#include "systems/MoveSys.hpp"
#include "systems/PauseSys.hpp"
#include "systems/BorderSys.hpp"

#include "TextureManager.hpp"

int main (void) {
    ECS ecs;
    Rtype::Client::TextureManager myTextures;
    ecs.register_component<Rtype::Client::Window>();
    ecs.register_component<Rtype::Client::Type>();
    ecs.register_component<Rtype::Client::Position>();
    ecs.register_component<Rtype::Client::Velocity>();
    ecs.register_component<Rtype::Client::Drawable>();
    ecs.register_component<Rtype::Client::Playable>();
    ecs.register_component<Rtype::Client::Hitbox>();

    Entity window = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Type>(window, {Rtype::Client::WINDOW});
    ecs.add_component<Rtype::Client::Window>(window, {{1280, 720}});

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back1, {1280 / 2, 720 / 2});
    ecs.add_component<Rtype::Client::Velocity>(back1, {-1, 0});
    ecs.add_component<Rtype::Client::Type>(back1, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back1, {{1, 1}});
    ecs.add_component<Rtype::Client::Drawable>(back1, {myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back2, {1280 / 2 + 1280, 720 / 2});
    ecs.add_component<Rtype::Client::Velocity>(back2, {-1, 0});
    ecs.add_component<Rtype::Client::Type>(back2, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back2, {{1, 1}});
    ecs.add_component<Rtype::Client::Drawable>(back2, {myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity entity1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(entity1, {500, 500});
    ecs.add_component<Rtype::Client::Velocity>(entity1, {0, 0});
    ecs.add_component<Rtype::Client::Playable>(entity1, {1});
    ecs.add_component<Rtype::Client::Type>(entity1, {Rtype::Client::PLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(entity1, {{0.1, 0.18}, true});
    ecs.add_component<Rtype::Client::Drawable>(entity1, {myTextures.getTexture("assets/images/ship/enemy_ship_1.png"), {2030, 1450}, {290, 290}, 35});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto pauseSys = Rtype::Client::PauseSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Drawable>(pauseSys);
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Velocity>(pauseSys);

    auto moveSys = Rtype::Client::MoveSys();
    ecs.subscribe<Rtype::Client::TicEvent, Rtype::Client::Position, Rtype::Client::Velocity>(moveSys);
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Playable, Rtype::Client::Velocity>(moveSys);

    auto frameSys = Rtype::Client::FrameSys();
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Drawable>(frameSys);

    auto borderSys = Rtype::Client::BorderSys();
    ecs.subscribe<Rtype::Client::TicEvent, Rtype::Client::Window, Rtype::Client::Type, Rtype::Client::Hitbox, Rtype::Client::Position>(borderSys);

    bool running = true;
    ecs.subscribe<Rtype::Client::InputEvent>(
        [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
            if ((e_input._event.type == sf::Event::KeyPressed &&
                e_input._event.key.code == sf::Keyboard::Escape) || e_input._event.type == sf::Event::Closed){
                running = false;
            }
        });

    auto windowSys = Rtype::Client::WindowSys({1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Drawable>(windowSys);

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
