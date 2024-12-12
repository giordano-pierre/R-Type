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
#include "components/Tag.hpp"
#include "components/Hitbox.hpp"
#include "components/Window.hpp"
#include "components/Selectable.hpp"
#include "components/Text.hpp"

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
    Rtype::Client::TupleUInt serverSize = {640, 360};
    ECS ecs;
    ecs.register_component<Rtype::Client::Window>();
    ecs.register_component<Rtype::Client::Tag>();
    ecs.register_component<Rtype::Client::Position>();
    ecs.register_component<Rtype::Client::Velocity>();
    ecs.register_component<Rtype::Client::Drawable>();
    ecs.register_component<Rtype::Client::Playable>();
    ecs.register_component<Rtype::Client::Hitbox>();
    ecs.register_component<Rtype::Client::Text>();

    Entity window = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Tag>(window, {Rtype::Client::WINDOW});
    ecs.add_component<Rtype::Client::Window>(window, {"assets/font/retro_gaming.ttf", {1280, 720}, serverSize});
    auto myWindow = ecs.get_components<Rtype::Client::Window>();

    Entity back1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back1, {serverSize.x / float(2), serverSize.y / float(2)});
    ecs.add_component<Rtype::Client::Velocity>(back1, {-1, 0});
    ecs.add_component<Rtype::Client::Tag>(back1, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back1, {{1, 1}, false});
    ecs.add_component<Rtype::Client::Drawable>(back1, {myWindow[0].value()._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity back2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(back2, {serverSize.x / float(2) + serverSize.x, serverSize.y / float(2)});
    ecs.add_component<Rtype::Client::Velocity>(back2, {-1, 0});
    ecs.add_component<Rtype::Client::Tag>(back2, {Rtype::Client::BACKGROUND});
    ecs.add_component<Rtype::Client::Hitbox>(back2, {{1, 1}, false});
    ecs.add_component<Rtype::Client::Drawable>(back2, {myWindow[0].value()._myTextures.getTexture("assets/images/background/background_mountain.jpg"), {675, 360}, {675, 360}, 1});

    Entity entity1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(entity1, {float(100), serverSize.y / float(2)});
    ecs.add_component<Rtype::Client::Velocity>(entity1, {0, 0});
    ecs.add_component<Rtype::Client::Playable>(entity1, {1});
    ecs.add_component<Rtype::Client::Tag>(entity1, {Rtype::Client::PLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(entity1, {{0.1, 0.18}});
    ecs.add_component<Rtype::Client::Drawable>(entity1, {myWindow[0].value()._myTextures.getTexture("assets/images/ship/enemy_ship_1.png"), {2030, 1450}, {290, 290}, 35});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto windowSys = Rtype::Client::WindowSys({1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Drawable, Rtype::Client::Text>(windowSys);

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
    ecs.subscribe<Rtype::Client::TicEvent, Rtype::Client::Window, Rtype::Client::Tag, Rtype::Client::Hitbox, Rtype::Client::Position>(borderSys);

    auto shootSys = Rtype::Client::ShootSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window, Rtype::Client::Playable, Rtype::Client::Position, Rtype::Client::Hitbox>(shootSys);

    bool running = true;
    ecs.subscribe<Rtype::Client::InputEvent>(
        [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
            if (e_input._myEvent == Rtype::Client::QUIT || e_input._event.type == sf::Event::Closed){
                running = false;
            }
        });

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

    Entity window = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Tag>(window, {Rtype::Client::WINDOW});
    ecs.add_component<Rtype::Client::Window>(window, {"assets/font/retro_gaming.ttf", {1280, 720}, serverSize});
    auto myWindow = ecs.get_components<Rtype::Client::Window>();

    Entity button = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 2});
    ecs.add_component<Rtype::Client::Tag>(button, {Rtype::Client::MENU});
    ecs.add_component<Rtype::Client::Hitbox>(button, {{0.48, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(button, {"START", myWindow[0].value()._font, {0.5, 0.5}, 0, 40, sf::Color::White});
    ecs.add_component<Rtype::Client::Drawable>(button, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Start the game !" << std::endl;}});

    Entity button2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button2, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 3});
    ecs.add_component<Rtype::Client::Tag>(button2, {Rtype::Client::MENU});
    ecs.add_component<Rtype::Client::Hitbox>(button2, {{0.48,float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(button2, {"CUSTOM", myWindow[0].value()._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(button2, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button2, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Custom your ship !" << std::endl;}});

    Entity button3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button3, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 4});
    ecs.add_component<Rtype::Client::Tag>(button3, {Rtype::Client::MENU});
    ecs.add_component<Rtype::Client::Hitbox>(button3, {{0.48,float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(button3, {"CONFIGS", myWindow[0].value()._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(button3, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button3, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), [](ECS ecs){std::cout << "Open Parameters !" << std::endl;}});

    Entity button4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(button4, {float(serverSize.x) / 2, float(serverSize.y) / 7 * 5});
    ecs.add_component<Rtype::Client::Tag>(button4, {Rtype::Client::MENU});
    ecs.add_component<Rtype::Client::Hitbox>(button4, {{0.48, float(1) / 10}});
    ecs.add_component<Rtype::Client::Text>(button4, {"QUIT", myWindow[0].value()._font, {0.5, 0.5}, 0, 40, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(button4, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});
    ecs.add_component<Rtype::Client::Selectable>(button4, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"),[](ECS &ecs){ecs.post<Rtype::Client::InputEvent>({sf::Event(), Rtype::Client::QUIT});}});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto windowSys = Rtype::Client::WindowSys({1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Drawable, Rtype::Client::Text>(windowSys);

    auto cheatSys = Rtype::Client::CheatSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys);

    auto selSys = Rtype::Client::SelectSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Position, Rtype::Client::Drawable, Rtype::Client::Hitbox, Rtype::Client::Selectable>(selSys);

    auto pressSys = Rtype::Client::PressButtonSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Selectable>(pressSys);

    bool running = true;
    ecs.subscribe<Rtype::Client::InputEvent>(
        [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
            if (e_input._myEvent == Rtype::Client::QUIT || e_input._event.type == sf::Event::Closed){
                running = false;
            }
        });

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
int mainTestConfig (void) {
    Rtype::Client::TupleUInt serverSize = {1920, 1080};
    ECS ecs;
    ecs.register_component<Rtype::Client::Window>();
    ecs.register_component<Rtype::Client::Tag>();
    ecs.register_component<Rtype::Client::Position>();
    ecs.register_component<Rtype::Client::Drawable>();
    ecs.register_component<Rtype::Client::Hitbox>();
    ecs.register_component<Rtype::Client::Selectable>();
    ecs.register_component<Rtype::Client::Text>();

    Entity window = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Tag>(window, {Rtype::Client::WINDOW});
    ecs.add_component<Rtype::Client::Window>(window, {"assets/font/retro_gaming.ttf", {1280, 720}, serverSize});
    auto myWindow = ecs.get_components<Rtype::Client::Window>();

    Entity param1 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param1, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 2});
    ecs.add_component<Rtype::Client::Tag>(param1, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param1, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param1, {"Press a button: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White});
    ecs.add_component<Rtype::Client::Drawable>(param1, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param2 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param2, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 3});
    ecs.add_component<Rtype::Client::Tag>(param2, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param2, {{0.48,float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param2, {"Pause the game: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param2, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param3 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param3, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 4});
    ecs.add_component<Rtype::Client::Tag>(param3, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param3, {{0.48,float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param3, {"Quit the game: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param3, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param4 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param4, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 5});
    ecs.add_component<Rtype::Client::Tag>(param4, {Rtype::Client::CGENERAL});
    ecs.add_component<Rtype::Client::Hitbox>(param4, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param4, {"Go back to menu: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param4, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param5 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param5, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 6});
    ecs.add_component<Rtype::Client::Tag>(param5, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param5, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param5, {"Move Up: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param5, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param6 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param6, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 7});
    ecs.add_component<Rtype::Client::Tag>(param6, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param6, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param6, {"Move Down: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param6, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param7 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param7, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 8});
    ecs.add_component<Rtype::Client::Tag>(param7, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param7, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param7, {"Move Left: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param7, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param8 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param8, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 9});
    ecs.add_component<Rtype::Client::Tag>(param8, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param8, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param8, {"Move Right: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param8, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param9 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param9, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 10});
    ecs.add_component<Rtype::Client::Tag>(param9, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param9, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param9, {"Shoot: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param9, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    Entity param10 = ecs.spawn_entity();
    ecs.add_component<Rtype::Client::Position>(param10, {float(serverSize.x) / 4 * 3, float(serverSize.y) / 15 * 11});
    ecs.add_component<Rtype::Client::Tag>(param10, {Rtype::Client::CPLAYER});
    ecs.add_component<Rtype::Client::Hitbox>(param10, {{0.48, float(1) / 18}});
    ecs.add_component<Rtype::Client::Text>(param10, {"Super Shoot: ", myWindow[0].value()._font, {0.5, 0.5}, 0.05, 30, sf::Color::White, sf::Text::Style::Regular});
    ecs.add_component<Rtype::Client::Drawable>(param10, {myWindow[0].value()._myTextures.getTexture("assets/images/utils/Btn_V03.png"), {366, 67}, {366, 67}, 1});

    ecs.register_event<Rtype::Client::FrameEvent>();
    ecs.register_event<Rtype::Client::InputEvent>();
    ecs.register_event<Rtype::Client::TicEvent>();

    auto windowSys = Rtype::Client::WindowSys({1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<Rtype::Client::FrameEvent, Rtype::Client::Window, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Drawable, Rtype::Client::Text>(windowSys);

    auto cheatSys = Rtype::Client::CheatSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Window>(cheatSys);

    auto selSys = Rtype::Client::SelectSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Position, Rtype::Client::Drawable, Rtype::Client::Hitbox, Rtype::Client::Selectable>(selSys);

    auto pressSys = Rtype::Client::PressButtonSys();
    ecs.subscribe<Rtype::Client::InputEvent, Rtype::Client::Position, Rtype::Client::Hitbox, Rtype::Client::Selectable>(pressSys);

    bool running = true;
    ecs.subscribe<Rtype::Client::InputEvent>(
        [&running](ECS &, const Rtype::Client::InputEvent &e_input) -> void {
            if (e_input._myEvent == Rtype::Client::QUIT || e_input._event.type == sf::Event::Closed){
                running = false;
            }
        });

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
