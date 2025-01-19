/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_main
*/
#include <iostream>

#include "ClientHandlerSystem.hpp"
#include "ECS/ECS.hpp"
#include "clientTools.hpp"
#include "createEntities.hpp"
#include "ecsObjects.hpp"
#include "loadSystems.hpp"
#include "systems/MessageHandlerSys.hpp"
#include "systems/UDPClient.hpp"

bool is_number(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]) || str[i] != '.')
            return false;
    }
    return true;
}

void createWindow(ECS &ecs) {
    rtype::client::TupleUInt serverSize = {1920, 1080};
    sf::Shader myShader;
    myShader.loadFromMemory(
        R"(
            uniform sampler2D texture;
            void main()
            {
                vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

                // Apply a color-blind friendly filter (Protanopia example)
                float r = 0.567 * pixel.r + 0.433 * pixel.g;
                float g = 0.558 * pixel.r + 0.442 * pixel.g;
                float b = pixel.b;

                gl_FragColor = vec4(r, g, b, pixel.a);
            }
            )",
        sf::Shader::Fragment);

    Entity base = ecs.spawn_entity();
    ecs.add_component<rtype::client::Tag>(base, {});
    ecs.add_component<rtype::client::Configs>(base, {{1440, 810}, serverSize});
    ecs.add_component<rtype::client::SFMLObjects>(
        base, {"assets/font/retro_gaming.ttf", myShader});
    ecs.add_component<rtype::client::Room>(base, {});
    ecs.add_component<rtype::client::PlayerInfo>(base, {});
}

int main(int ac, char *argv[]) {
    if (ac != 3 && ac != 1)
        return 84;

    std::string host = (ac == 1) ? "127.0.0.1" : argv[1];
    std::string port = (ac == 1) ? "4242" : argv[2];
    if (ac == 3 && (!is_number(host.data()) || !is_number(port.data())))
        return 84;

    ECS ecs;
    ecs.register_component<rtype::client::Drawable>();
    ecs.register_component<rtype::client::Health>();
    ecs.register_component<rtype::client::Hitbox>();
    ecs.register_component<rtype::client::LastUpdate>();
    ecs.register_component<rtype::client::Playable>();
    ecs.register_component<rtype::client::PlayerData>();
    ecs.register_component<rtype::client::Position>();
    ecs.register_component<rtype::client::Pressable>();
    ecs.register_component<rtype::client::Scene>();
    ecs.register_component<rtype::client::Score>();
    ecs.register_component<rtype::client::Selectable>();
    ecs.register_component<rtype::client::Tag>();
    ecs.register_component<rtype::client::Text>();
    ecs.register_component<rtype::client::Velocity>();
    ecs.register_component<rtype::client::Configs>();
    ecs.register_component<rtype::client::SFMLObjects>();
    ecs.register_component<rtype::client::Room>();
    ecs.register_component<rtype::client::PlayerInfo>();

    ecs.register_event<rtype::client::FrameEvent>();
    ecs.register_event<rtype::client::InputEvent>();
    ecs.register_event<rtype::client::TicEvent>();
    ecs.register_event<rtype::client::ChangeKey>();
    ecs.register_event<rtype::client::CreationEvent>();
    ecs.register_event<rtype::client::DeleteEvent>();
    ecs.register_event<rtype::client::AnimeEvent>();
    ecs.register_event<RequestEvent>();
    ecs.register_event<ReceiveEvent>();

    createWindow(ecs);

    rtype::client::UDPClient client(ecs, host, port);
    ecs.subscribe<RequestEvent>(client, true);

    rtype::client::MessageHandlerSys handler;
    ecs.subscribe<ReceiveEvent, rtype::client::Room, rtype::client::SFMLObjects,
                  rtype::client::Tag, rtype::client::Position,
                  rtype::client::Velocity, rtype::client::Health,
                  rtype::client::Score, rtype::client::LastUpdate>(handler,
                                                                   true);

    auto lifeSys = rtype::client::LifeSys();
    ecs.subscribe<rtype::client::CreationEvent, rtype::client::Configs,
                  rtype::client::SFMLObjects, rtype::client::PlayerInfo,
                  rtype::client::Room>(lifeSys, true);
    ecs.subscribe<rtype::client::DeleteEvent, rtype::client::Scene>(lifeSys,
                                                                    true);

    auto windowSys = rtype::client::WindowSys(
        {1920, 1080, 32}, "R-type", sf::Style::Titlebar | sf::Style::Close);
    ecs.subscribe<rtype::client::FrameEvent, rtype::client::Configs,
                  rtype::client::SFMLObjects, rtype::client::Position,
                  rtype::client::Hitbox, rtype::client::Drawable,
                  rtype::client::Text, rtype::client::Selectable>(windowSys,
                                                                  true);
    ecs.subscribe<rtype::client::ChangeKey, rtype::client::Configs>(windowSys,
                                                                    true);

    auto cheatSys = rtype::client::CheatSys();
    ecs.subscribe<rtype::client::InputEvent, rtype::client::Configs>(cheatSys,
                                                                     true);

    auto frameSys = rtype::client::AnimeSys();
    ecs.subscribe<rtype::client::AnimeEvent, rtype::client::Drawable>(frameSys,
                                                                      true);

    bool running = true;
    ecs.subscribe<ReceiveEvent>(
        [&running](ECS &ecs, const ReceiveEvent &rec_event) -> void {
            if (rec_event.action == DISCONNECT)
                running = false;
        },
        true);

    ecs.subscribe<rtype::client::InputEvent>(
        [&client, &running](ECS &ecs,
                            const rtype::client::InputEvent &e_input) -> void {
            if (e_input._myEvent == rtype::client::QUIT ||
                e_input._event.type == sf::Event::Closed) {
                // std::cout << "FIX1" << std::endl;
                if (client.isConnected())
                    ecs.post<RequestEvent>({DISCONNECT, {}});
                else
                    running = false;
                // std::cout << "FIX2" << std::endl;
            }
        },
        true);

    ecs.post<RequestEvent>({Protocol::CONNECT, {}});
    ecs.post<rtype::client::CreationEvent>({rtype::client::MENU});
    ecs.post<rtype::client::CreationEvent>({rtype::client::M_GENERAL});

    const auto FPS = 60;
    const timer::duration<double, std::ratio<1, FPS>> frameRate(1);
    timer::time_point<timer::steady_clock> frameStart;
    timer::duration<double> dtimeF = timer::duration<double>::zero();

    const auto Animation = 25;
    const timer::duration<double, std::ratio<1, Animation>> animeRate(1);
    timer::time_point<timer::steady_clock> animeStart;
    timer::duration<double> dtimeA = timer::duration<double>::zero();

    timer::time_point<timer::steady_clock> newTime;

    bool trigger;
    while (running) {
        trigger = false;
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
                auto &evt = ecs.front();
                evt();
                ecs.pop_front();
            }
        }
    }
    return 0;
}
