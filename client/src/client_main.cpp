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
#include "components/Selectable.hpp"

#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"

#include "systems/WindowSys.hpp"
#include "systems/FrameSys.hpp"
#include "systems/MoveSys.hpp"
#include "systems/PauseSys.hpp"
#include "systems/BorderSys.hpp"
#include "systems/ShootSys.hpp"
#include "systems/CheatSys.hpp"
#include "systems/SelectSys.hpp"
#include "systems/PressButtonSys.hpp"

#include "TextureManager.hpp"

int main (void) {
// int mainTestGame (void) {
    ECS ecs;
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

    auto myWindow = ecs.get_components<Rtype::Client::Window>();

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back1, {1280 / 2, 720 / 2});
    ecs.add_component<Rtype::Client::Velocity>(back1, {-1, 0});
    ecs.add_component<Rtype::Client::Type>(back1, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Rtype::Client::Drawable>(back1, {myWindow[0].value()._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back2, {1280 / 2 + 1280, 720 / 2});
    ecs.add_component<Rtype::Client::Velocity>(back2, {-1, 0});
    ecs.add_component<Rtype::Client::Type>(back2, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Rtype::Client::Drawable>(back2, {myWindow[0].value()._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity entity1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(entity1, {500, 500});
    ecs.add_component<Rtype::Client::Velocity>(entity1, {0, 0});
    ecs.add_component<Rtype::Client::Playable>(entity1, {1});
    ecs.add_component<Rtype::Client::Type>(entity1, {Rtype::Client::PLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(entity1, {{0.1, 0.18}});
    ecs.add_component<Rtype::Client::Drawable>(entity1, {myWindow[0].value()._myTextures.getTexture("assets/images/ship/enemy_ship_1.png"), {2030, 1450}, {290, 290}, 35});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto pauseSys = Rtype::Client::PauseSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Drawable>(pauseSys);
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Velocity>(pauseSys);

    auto cheatSys = Rtype::Client::CheatSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys);

    auto moveSys = Rtype::Client::MoveSys();
    ecs.subscribe<Rtype::Client::TicEvent, Rtype::Client::Position, Rtype::Client::Velocity>(moveSys);
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Playable, Rtype::Client::Velocity>(moveSys);

    auto frameSys = Rtype::Client::FrameSys();
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Drawable>(frameSys);

    auto borderSys = Rtype::Client::BorderSys();
    ecs.subscribe<Rtype::Client::TicEvent, Rtype::Client::Window, Rtype::Client::Type, Rtype::Client::Hitbox, Rtype::Client::Position>(borderSys);

    auto shootSys = Rtype::Client::ShootSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window, Rtype::Client::Playable, Rtype::Client::Position, Rtype::Client::Hitbox>(shootSys);

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


// int main (void) {
int mainTestMenu (void) {
    ECS ecs;
    ecs.register_component<Rtype::Client::Window>();
    ecs.register_component<Rtype::Client::Type>();
    ecs.register_component<Rtype::Client::Position>();
    ecs.register_component<Rtype::Client::Velocity>();
    ecs.register_component<Rtype::Client::Drawable>();
    ecs.register_component<Rtype::Client::Playable>();
    ecs.register_component<Rtype::Client::Hitbox>();
    ecs.register_component<Rtype::Client::Selectable>();

    Entity window = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Type>(window, {Rtype::Client::WINDOW});
    ecs.add_component<Rtype::Client::Window>(window, {{1280, 720}});
    auto myWindow = ecs.get_components<Rtype::Client::Window>();

    Entity button = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button, {1280 / 2 - 400, 720 / 6});
    ecs.add_component<Rtype::Client::Type>(button, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 1 is clicked!" << std::endl;}});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button2, {1280 / 2, 720 / 6});
    ecs.add_component<Rtype::Client::Type>(button2, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button2, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button2, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button2, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 2 is clicked!" << std::endl;}});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button3, {1280 / 2 + 400, 720 / 6});
    ecs.add_component<Rtype::Client::Type>(button3, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button3, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button3, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button3, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 3 is clicked!" << std::endl;}});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button4, {1280 / 2 - 400, 720 / 3});
    ecs.add_component<Rtype::Client::Type>(button4, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button4, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button4, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button4, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 4 is clicked!" << std::endl;}});

    Entity button5 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button5, {1280 / 2, 720 / 3});
    ecs.add_component<Rtype::Client::Type>(button5, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button5, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button5, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button5, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 5 is clicked!" << std::endl;}});

    Entity button6 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button6, {1280 / 2 + 400, 720 / 3});
    ecs.add_component<Rtype::Client::Type>(button6, {Rtype::Client::BUTTON});
    ecs.add_component<Rtype::Client::Hitbox>(button6, {{0.3, 0.1}});
    ecs.add_component<Rtype::Client::Drawable>(button6, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button.png"), {200, 30}, {200, 30}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button6, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/start_button_selected.png"), [](ECS ecs){std::cout << "Button 6 is clicked!" << std::endl;}});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto cheatSys = Rtype::Client::CheatSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys);

    auto selSys = Rtype::Client::SelectSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Position, Rtype::Client::Drawable, Rtype::Client::Hitbox, Rtype::Client::Selectable>(selSys);

    auto pressSys = Rtype::Client::PressButtonSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Selectable>(pressSys);

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
